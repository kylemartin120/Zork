#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Trigger.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trigger;

class GameObject {
 private:
  string name;
  string description;
  string status;
  vector<Trigger*> trigs;

 public:
  GameObject(string n, string d, string s, vector<Trigger*> t);
  virtual ~GameObject();
  string getName();
  void printDescription();
  string getStatus();
  bool testTrigs(); // true if any of the triggers are true
  virtual bool contains(GameObject* obj);
};
#endif
