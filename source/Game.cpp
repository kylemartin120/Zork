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
}

Game::~Game() {}

GameObject* Game::getObject(string name) {
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->name == name) {
      return objects[i];
    }
  }

  return NULL;
}

Item* Game::getItem(string name) {
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->name == name) {
      return items[i];
    }
  }

  return NULL;
}

Creature* Game::getCreature(string name) {
  for (int i = 0; i < creatures.size(); i++) {
    if (creatures[i]->name == name) {
      return creatures[i];
    }
  }

  return NULL;
}

Container* Game::getContainer(string name) {
  for (int i = 0; i < containers.size(); i++) {
    if (containers[i]->name == name) {
      return containers[i];
    }
  }

  return NULL;
}

bool Game::inInventory(string name) {
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i] == name) {
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
    for (int j = 0; j < cur_conds.size(); j++) {
      if (!isMet(cur_conds[j])) {
	act = false;
	j = cur_conds.size();
      }
    }
    if (act) {
      for (int j = 0; j < cur_comms.size(); j++) {
	  if (cur_comms[j] != input) {
	    act = false;
	    j = cur_comms.size();
	  }
	}
    }

    if (act) {
      // act on trigger
      return true;
    }
    
  }
  return false;
}

bool Game::isMet(Condition* cond) {
  if (cond->hasType()) {
    HasCondition* has_cond = (HasCondition*) cond;
    bool hasObject;
    if (has_cond->owner == "inventory") {
      hasObject = inInventory(has_cond->object);
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
