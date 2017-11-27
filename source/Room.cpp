#include "Room.h"
#include "GameObject.h"
#include "Border.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

Room::Room(string n, string s, string t, string d, vector<Border*> b,
	   vector<string> c, vector<string> i, vector<string> cr,
	   vector<string> o, vector<Trigger*> trigs) :
  GameObject(n, s, d, trigs) {
  type = t;
  borders = b;
  containers = c;
  items = i;
  creatures = cr;
  objects = o;
}

Room::Room(xml_node<>* node) : GameObject(node) {
  if (node->first_node("type") == NULL) {
    type = "regular";
  }
  else {
    type = node->first_node("type")->value();
  }

  for (xml_node<>* cur_node = node->first_node("border");
       cur_node; cur_node = cur_node->next_sibling("border")) {
    Border* border = new Border(cur_node);
    borders.push_back(border);
  }

  for (xml_node<>* cur_node = node->first_node("container");
       cur_node; cur_node = cur_node->next_sibling("container")) {
    containers.push_back(cur_node->value());
    objects.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("item");
       cur_node; cur_node = cur_node->next_sibling("item")) {
    items.push_back(cur_node->value());
    objects.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("creature");
       cur_node; cur_node = cur_node->next_sibling("creature")) {
    creatures.push_back(cur_node->value());
    objects.push_back(cur_node->value());
  }

  obj_type = "room";
}

Room::~Room() {}

string Room::checkBorders(string direction) {
  for (unsigned int i = 0; i < borders.size(); i++) {
    if (borders[i]->getDirection().at(0) == direction.at(0)) {
      return borders[i]->getName();
    }
  }

  // no border in this direction
  return "Can't go that way";
}

vector<string> Room::getContainers() {
  return containers;
}

vector<string> Room::getItems() {
  return items;
}

vector<string> Room::getCreatures() {
  return creatures;
}

void Room::putItem(string item) {
  items.push_back(item);
}
