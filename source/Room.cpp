#include "Room.h"
#include "GameObject.h"
#include "Border.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

Room::Room(string n, string s, string t, string d, vector<Border*> b,
	   vector<Item*> i, vector<Creature*> c, vector<Trigger*> trigs) :
  GameObject(n, s, d, trigs) {
  type = t;
  borders = b;
  items = i;
  creatures = c;
  triggers = trigs;
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

vector<Container*> Room::getContainers() {
  return containers;
}

vector<Item*> Room::getItems() {
  return items;
}

vector<Creature*> Room::getCreatures() {
  return creatures;
}

vector<Trigger*> Room::getTriggers() {
  return triggers;
}
