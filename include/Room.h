#ifndef ROOM_H_
#define ROOM_H_

#include "GameObject.h"
#include "Border.h"

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
  Room(string n, string stat, string t, string d, vector<Border*> b,
       vector<Item*> i, vector<Creature*> c, vector<Trigger*> trigs);
  virtual ~Room();
  string checkBorders(string direction);
  vector<Container*> getContainers();
  vector<Item*> getItems();
  vector<Creature*> getCreatures();
  vector<Trigger*> getTriggers();
};
#endif
