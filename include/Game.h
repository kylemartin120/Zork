#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "rapidxml.hpp"
#include <vector>
#include <queue>

#include "Item.h"
#include "Container.h"
#include "GameObject.h"
#include "Room.h"
#include "Trigger.h"

using namespace std;
using namespace rapidxml;

class Game {
 public:
  vector<Room*> rooms;
  vector<Item*> items;
  vector<Container*> containers;
  vector<Creature*> creatures;
  vector<string> inventory;
  vector<GameObject*> objects;
  string input;
  Room* cur_room;

  Game(string filename);
  virtual ~Game();

  // finding objects
  GameObject* getObject(string name);
  Item* getItem(string name);
  Creature* getCreature(string name);
  Container* getContainer(string name);
  bool inInventory(string name);

  // running the game
  bool checkTriggers(vector<Trigger*> triggers);
  bool isMet(Condition* cond);
  bool checkAllTriggers();
  void handleCommand(string command);
  void printInventory();
  void move(string dir);
  void putItem(Item* i, Container* c); // used for take as well
  void open(Container* c);
  void exitGame(); // if current room is type "exit", leave game
  void drop(Item* i);
  bool turnOn(Item* i);
  
};
#endif
