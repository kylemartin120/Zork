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

bool checkTriggers(vector<Trigger*> triggers) {
  for (int i = 0; i < triggers.size(); i++) {
  }
  return false;
}
