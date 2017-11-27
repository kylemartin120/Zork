#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include "rapidxml.hpp"
#include <vector>

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
  bool gameOver;
  int turn_num;

  Game(string filename);
  virtual ~Game();

  // finding objects
  GameObject* getObject(string name);
  Item* getItem(string name);
  Creature* getCreature(string name);
  Container* getContainer(string name);
  Room* getRoom(string name);
  bool inInventory(string name);

  // running the game
  bool checkTriggers(vector<Trigger*> triggers);
  bool isMet(Condition* cond);
  bool checkAllTriggers();
  void handleCommand(string command);
  void handleAction(string action);
  void printInventory();
  void move(string dir);
  void take(Item* i);
  void take(Item* i, Container* c);
  void put(Item* i, Container* c);
  void open(Container* c);
  void exitGame(); // if current room is type "exit", leave game
  void drop(Item* i);
  void turnOn(Item* i);
  void read(Item* i);
  void attack(Item* i, Creature* c);
  void addObject(GameObject* o, Room* r);
  void addObject(GameObject* o, Container* c);
  void delObject(GameObject* o);
  void update(GameObject* o, string s);
  void endGame();
  
};
#endif
