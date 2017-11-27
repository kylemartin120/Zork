#include "Game.h"

Game::Game(string filename) {
  xml_document<> doc;
  xml_node<>* root_node;

  ifstream theFile(filename.c_str());
  vector<char> buffer((istreambuf_iterator<char>(theFile)),
		      istreambuf_iterator<char>());
  buffer.push_back('\0');
  doc.parse<0>(&buffer[0]);
  root_node = doc.first_node();
  
  for (xml_node<>* cur_node = root_node->first_node("room");
       cur_node; cur_node = cur_node->next_sibling("room")) {
    Room* this_room = new Room(cur_node);
    rooms.push_back(this_room);
    objects.push_back(this_room);
  }

  for (xml_node<>* cur_node = root_node->first_node("item");
       cur_node; cur_node = cur_node->next_sibling("item")) {
    Item* this_item = new Item(cur_node);
    items.push_back(this_item);
    objects.push_back(this_item);
  }

  for (xml_node<>* cur_node = root_node->first_node("container");
       cur_node; cur_node = cur_node->next_sibling("container")) {
    Container* this_container = new Container(cur_node);
    containers.push_back(this_container);
    objects.push_back(this_container);
  }

  for (xml_node<>* cur_node = root_node->first_node("creature");
       cur_node; cur_node = cur_node->next_sibling("creature")) {
    Creature* this_creature = new Creature(cur_node);
    creatures.push_back(this_creature);
    objects.push_back(this_creature);
    }

  cur_room = rooms[0];
  input = "";
  gameOver = false;
  turn_num = 0;
}

Game::~Game() {}

GameObject* Game::getObject(string name) {
  for (int i = 0; i < objects.size(); i++) {
    if ((string) objects[i]->name == name) {
      return objects[i];
    }
  }

  return NULL;
}

Item* Game::getItem(string name) {
  for (int i = 0; i < items.size(); i++) {
    if ((string) items[i]->name == name) {
      return items[i];
    }
  }

  return NULL;
}

Creature* Game::getCreature(string name) {
  for (int i = 0; i < creatures.size(); i++) {
    if ((string) creatures[i]->name == name) {
      return creatures[i];
    }
  }

  return NULL;
}

Container* Game::getContainer(string name) {
  for (int i = 0; i < containers.size(); i++) {
    if ((string) containers[i]->name == name) {
      return containers[i];
    }
  }

  return NULL;
}

Room* Game::getRoom(string name) {
  for (int i = 0; i < rooms.size(); i++) {
    if ((string) rooms[i]->name == name) {
      return rooms[i];
    }
  }
}

bool Game::inInventory(string name) {
  for (int i = 0; i < inventory.size(); i++) {
    if ((string) inventory[i] == name) {
      return true;
    }
  }

  return false;
}

bool Game::checkAllTriggers() {
  if (checkTriggers(cur_room->triggers)) {
    return true;
  }
  for (int i = 0; i < cur_room->objects.size(); i++) {
    GameObject* object = getObject(cur_room->objects[i]);
    if (checkTriggers(object->triggers)) {
      return true;
    }
  }

  return false;
}

bool Game::checkTriggers(vector<Trigger*> triggers) {
  for (int i = 0; i < triggers.size(); i++) {
    vector<Condition*> cur_conds = triggers[i]->conditions;
    vector<string> cur_comms = triggers[i]->commands;

    bool act = true;
    if (triggers[i]->used && !triggers[i]->permanent) {
      act = false;
    }
    else if (triggers[i]->last_used == turn_num) {
      act = false;
    }
    if (act) {
      for (int j = 0; j < cur_conds.size(); j++) {
	if (!isMet(cur_conds[j])) {
	  act = false;
	  j = cur_conds.size();
	}
      }
    }
    if (act) {
      for (int j = 0; j < cur_comms.size(); j++) {
	if ((string) cur_comms[j] != input) {
	    act = false;
	    j = cur_comms.size();
	  }
	}
    }

    if (act) {
      triggers[i]->used = true;
      triggers[i]->last_used = turn_num;
      for (int j = 0; j < triggers[i]->prints.size(); j++) {
	cout << triggers[i]->prints[j] << endl;
      }

      for (int j = 0; j < triggers[i]->actions.size(); j++) {
	handleAction(triggers[i]->actions[j]);
      }
      
      return true;
    }
    
  }
  return false;
}

bool Game::isMet(Condition* cond) {
  if (cond->hasType()) {
    HasCondition* has_cond = (HasCondition*) cond;
    bool hasObject;
    if ((string) has_cond->owner == "inventory") {
      hasObject = inInventory(has_cond->object);
      if (hasObject) {
      }
    }
    else {
      Container* owner = getContainer(has_cond->owner);
      hasObject = owner->contains(has_cond->object);
    }
    return (has_cond->has == hasObject);
  }

  StatusCondition* stat_cond = (StatusCondition*) cond;
  GameObject* object = getObject(stat_cond->object);
  return (stat_cond->status == object->status);
}

void Game::handleCommand(string command) {

  istringstream buf(command);
  istream_iterator<string> beg(buf), end;
  vector<string> parts(beg, end);

  input = command;

  if (input == "") {
    cout << "No input detected." << endl;
    return;
  }
  
  else if (input == "n" || input == "e" || input == "s" || input == "w") {
    move(input);
  }

  else if (input == "i") {
    printInventory();
  }

  else if (input == "open exit") {
    exitGame();
  }

  else if (parts[0] == "take") {
    for (int i = 0; i < cur_room->items.size(); i++) {
      if (parts[1] == cur_room->items[i]) {
	Item* i = getItem(parts[1]);
	take(i);
	return;
      }
    }

    for (int i = 0; i < cur_room->containers.size(); i++) {
      Container* c = getContainer(cur_room->containers[i]);
      for (int j = 0; j < c->items.size(); j++) {
	if (parts[1] == c->items[j]) {
	  Item* i = getItem(parts[1]);
	  take(i, c);
	  return;
	}
      }
    }

    cout << "Couldn't find item." << endl;
  }

  else if (parts[0] == "open") {
    for (int i = 0; i < cur_room->containers.size(); i++) {
      if (cur_room->containers[i] == parts[1]) {
	Container* c = getContainer(cur_room->containers[i]);
	open(c);
	return;
      }
    }

    cout << "Couldn't find container." << endl;
  }

  else if (parts[0] == "read") {
    if (inInventory(parts[1])) {
      Item* i = getItem(parts[1]);
      read(i);
    }
    else {
      cout << "Item not in inventory." << endl;
    }
  }

  else if (parts[0] == "drop") {
    if (inInventory(parts[1])) {
      Item* i = getItem(parts[1]);
      drop(i);
    }
    else {
      cout << "Item not in inventory." << endl;
    }
  }

  else if (parts[0] == "put" && parts[2] == "in") {
    if (inInventory(parts[1])) {
      for (int i = 0; i < cur_room->containers.size(); i++) {
	if (cur_room->containers[i] == parts[3]) {
	  Container* c = getContainer(cur_room->containers[i]);
	  Item* it = getItem(parts[1]);
	  put(it, c);
	  return;
	}
      }
      cout << "Container not found." << endl;
    }
    else {
      cout << "Item not in inventory." << endl;
    }
  }

  else if (parts[0] == "turn" && parts[1] == "on") {
    if (inInventory(parts[2])) {
      Item* i = getItem(parts[2]);
      turnOn(i);
    }
    else {
      cout << "Item not in inventory." << endl;
    }
  }

  else if (parts[0] == "attack" && parts[2] == "with") {
    if (inInventory(parts[3])) {
      for (int i = 0; i < cur_room->creatures.size(); i++) {
	if (parts[1] == cur_room->creatures[i]) {
	  Creature* c = getCreature(parts[1]);
	  Item* i = getItem(parts[3]);
	  attack(i, c);
	  return;
	}
      }
      cout << "Creature not in room." << endl;
    }
    else {
      cout << "Item not in inventory." << endl;
    }
  }

  else {
    cout << "Invalid input." << endl;
  }

  input = "";
}

void Game::handleAction(string action) {
  istringstream buf(action);
  istream_iterator<string> beg(buf), end;
  vector<string> parts(beg, end);

  if (parts[0] == "Update" && parts[2] == "to") {
    GameObject* o = getObject(parts[1]);
    if (o) {
      update(o, parts[3]);
    }
  }

  else if (parts[0] == "Delete") {
    GameObject* o = getObject(parts[1]);
    if (o) {
      delObject(o);
    }
  }

  else if (parts[0] == "Add" && parts[2] == "to") {
    GameObject* o = getObject(parts[1]);
    if (o) {
      for (int i = 0; i < rooms.size(); i++) {
	if ((string) rooms[i]->name == parts[3]) {
	  Room* r = rooms[i];
	  addObject(o, r);
	  return;
	}
      }
      for (int i = 0; i < rooms.size(); i++) {
	for (int j = 0; j < rooms[i]->containers.size(); j++) {
	  if (rooms[i]->containers[j] == parts[3]) {
	    Container* c = getContainer(parts[3]);
	    addObject(o, c);
	    return;
	  }
	}
      }
    }
  }

  else if (action == "Game Over") {
    endGame();
  }

  else {
    handleCommand(action);
  }
}

void Game::printInventory() {
  if (inventory.size() == 0) {
    cout << "Inventory: empty" << endl;
  }
  else {
    cout << "Inventory: ";
    for (int i = 0; i < inventory.size(); i++) {
      cout << inventory[i];
      if (i < inventory.size() - 1) {
	cout << ", ";
      }
      else {
	cout << endl;
      }
    }
  }
}

void Game::move(string dir) {
  string room_name = cur_room->checkBorders(dir);
  if (room_name == "Can't go that way") {
    cout << room_name << endl;
  }
  else {
    Room* r = getRoom(room_name);
    cur_room = r;
    cout << r->description << endl;
  }
}

void Game::take(Item* i) {
  string name = (string) i->name;
  inventory.push_back(name);
  for (int j = 0; j < cur_room->items.size(); j++) {
    if (cur_room->items[j] == name) {
      cur_room->items.erase(cur_room->items.begin() + j);
      j = cur_room->items.size();
    }
  }
  cout << "Item " << name << " added to inventory." << endl;
}

void Game::take(Item* i, Container* c) {
  if (!c->isOpened) {
    cout << "Couldn't find item" << endl;
    return;
  }
  string name = (string) i->name;
  inventory.push_back(name);
  for (int j = 0; j < c->items.size(); j++) {
    if (c->items[j] == name) {
      c->items.erase(c->items.begin() + j);
      j = c->items.size();
    }
  }
  cout << "Item " << name << " added to inventory." << endl;
}

void Game::put(Item* i, Container* c) {
  string name = (string) i->name;
  c->items.push_back(name);
  for (int j = 0; j < inventory.size(); j++) {
    if (inventory[j] == name) {
      inventory.erase(inventory.begin() + j);
      j = inventory.size();
    }
  }
  cout << "Item " << name << " added to " << c->name << "." << endl;
}

void Game::open(Container* c) {
  c->isOpened = true;
  if (c->items.size() == 0) {
    cout << c->name << " is empty." << endl;
  }
  else {
    cout << c->name << " contains ";
    for (int i = 0; i < c->items.size(); i++) {
      cout << c->items[i];
      if (i < c->items.size() - 1) {
	cout << ", ";
      }
      else {
	cout << endl;
      }
    }
  }
}

void Game::exitGame() {
  string cur_type = (string) cur_room->type;
  if (cur_type == "exit") {
    cout << "Game Over" << endl;
    gameOver = true;
  }
  else {
    cout << "Not an exit." << endl;
  }
}


void Game::read(Item* i) {
  if (((string) i->writing).size() > 0) {
    cout << (string) i->writing << endl;
  }
  else {
    cout << "Nothing written." << endl;
  }
}

void Game::drop(Item* i) {
  string name = (string) i->name;
  cout << name << " dropped." << endl;
  cur_room->items.push_back(name);
  for (int j = 0; j < inventory.size(); j++) {
    if (name == inventory[j]) {
      inventory.erase(inventory.begin() + j);
    }
  }
}

void Game::turnOn(Item* i) {
  string name = (string) i->name;
  cout << "You activate the " << name << "." << endl;
  for (int j = 0; j < i->prints.size(); j++) {
    cout << i->prints[j] << endl;
  }
  for (int j = 0; j < i->actions.size(); j++) {
    handleAction(i->actions[j]);
  }
}

void Game::endGame() {
  cout << "Victory!" << endl;
  gameOver = true;
}

void Game::attack(Item* i, Creature* c) {
  cout << "You assault the " << c->name << " with the " << i->name
       << "." << endl;
  if (c->doAttack((string) i->name)) {
    Attack* attack = c->getAttack();
    if (!attack) {
      return;
    }
    vector<Condition*> conds = attack->conditions;
    vector<string> prints = attack->prints;
    vector<string> actions = attack->actions;
    for (int j = 0; j < conds.size(); j++) {
      if (!isMet(conds[j])) {
	cout << "It doesn't work." << endl;
	return;
      }
    }
    for (int j = 0; j < prints.size(); j++) {
      cout << prints[j] << endl;
    }
    for (int j = 0; j < actions.size(); j++) {
      handleAction(actions[j]);
    }
  }
  else {
    cout << "It doesn't work." << endl;
  }
}

void Game::addObject(GameObject* o, Room* r) {
  r->objects.push_back((string) o->name);
  if (o->obj_type == "item") {
    r->items.push_back((string) o->name);
  }
  else if (o->obj_type == "creature") {
    r->creatures.push_back((string) o->name);
  }
  else if (o->obj_type == "container") {
    r->containers.push_back((string) o->name);
  }
}

void Game::addObject(GameObject* o, Container* c) {
  c->items.push_back((string) o->name);
}

void Game::delObject(GameObject* o) {
  for (int i = 0; i < objects.size(); i++) {
    if ((string) objects[i]->name == (string) o->name) {
      objects.erase(objects.begin() + i);
    }
  }

  for (int i = 0; i < rooms.size(); i++) {
    for (int j = 0; j < rooms[i]->objects.size(); j++) {
      if (rooms[i]->objects[j] == (string) o->name) {
	rooms[i]->objects.erase(rooms[i]->objects.begin() + j);
      }
    }
  }
  
  if (o->obj_type == "item") {
    for (int i = 0; i < items.size(); i++) {
      if ((string) items[i]->name == (string) o->name) {
	items.erase(items.begin() + i);
      }
    }
    
    for (int i = 0; i < rooms.size(); i++) {
      for (int j = 0; j < rooms[i]->items.size(); j++) {
	if ((string) o->name == rooms[i]->items[j]) {
	  rooms[i]->items.erase(rooms[i]->items.begin() + j);
	}
      }
    }

    for (int i = 0; i < containers.size(); i++) {
      for (int j = 0; j < containers[i]->items.size(); j++) {
	if ((string) o->name == containers[i]->items[j]) {
	  containers[i]->items.erase(containers[i]->items.begin() + j);
	}
      }
    }
  }

  else if (o->obj_type == "container") {
    for (int i = 0; i < containers.size(); i++) {
      if ((string) containers[i]->name == (string) o->name) {
	containers.erase(containers.begin() + i);
      }
    }
    
    for (int i = 0; i < rooms.size(); i++) {
      for (int j = 0; j < rooms[i]->containers.size(); j++) {
	if ((string) o->name == rooms[i]->containers[j]) {
	  rooms[i]->containers.erase(rooms[i]->containers.begin() +  j);
	}
      }
    }
  }

  else if (o->obj_type == "creature") {
    for (int i = 0; i < creatures.size(); i++) {
      if ((string) creatures[i]->name == (string) o->name) {
	creatures.erase(creatures.begin() + i);
      }
    }

    for (int i = 0; i < rooms.size(); i++) {
      for (int j = 0; j < rooms[i]->creatures.size(); j++) {
	if ((string) o->name == rooms[i]->creatures[j]) {
	  rooms[i]->creatures.erase(rooms[i]->creatures.begin() +  j);
	}
      }
    }
  }

  else if (o->obj_type == "room") {
    for (int i = 0; i < rooms.size(); i++) {
      if ((string) rooms[i]->name == (string) o->name) {
	rooms.erase(rooms.begin() + i);
      }
      
      for (int j = 0; j< rooms[i]->borders.size(); j++) {
	if ((string) o->name == (string) rooms[i]->borders[j]->name) {
	  rooms[i]->borders.erase(rooms[i]->borders.begin() + j);
	}
      }
    }
  }
}
  
void Game::update(GameObject* o, string s) {
  o->status = s;
}
