#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Trigger.h"

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Trigger;

class GameObject {
 public:
  string name;
  string description;
  string status;
  vector<Trigger*> triggers;
  string obj_type;

  GameObject(string n, string d, string s, vector<Trigger*> t);
  GameObject(xml_node<>* node);
  virtual ~GameObject();
  string getName();
  void printDescription();
  string getStatus();
  virtual bool contains(GameObject* obj);
};
#endif
