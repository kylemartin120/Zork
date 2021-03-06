#ifndef ROOM_H_
#define ROOM_H_

#include "GameObject.h"
#include "Border.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Room : public GameObject {
 public:
  string type;
  vector<Border*> borders;
  vector<string> containers;
  vector<string> items;
  vector<string> creatures;
  vector<string> objects;

  Room(string n, string s, string t, string d, vector<Border*> b,
       vector<string> c, vector<string> i, vector<string> cr,
       vector<string> o, vector<Trigger*> trigs);
  Room(xml_node<>* node);
  virtual ~Room();
  string checkBorders(string direction);
  vector<string> getContainers();
  vector<string> getItems();
  vector<string> getCreatures();
  void putItem(string item);
};
#endif
