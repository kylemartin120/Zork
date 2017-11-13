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

using namespace std;

class Room : public GameObject {
 private:
  string type;
  vector<Border*> borders;
  vector<Container*> containers;
  vector<Item*> items;
  vector<Creature*> creatures;
  vector<Trigger*> triggers;

 public:
  Room(string n, string s, string t, string d, vector<Border*> b,
       vector<Container*> c, vector<Item*> i, vector<Creature*> cr,
       vector<Trigger*> trigs);
  virtual ~Room();
  string checkBorders(string direction);
  vector<Container*> getContainers();
  vector<Item*> getItems();
  vector<Creature*> getCreatures();
  vector<Trigger*> getTriggers();
  void putItem(Item* item);
};
#endif
