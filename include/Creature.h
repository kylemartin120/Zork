#ifndef CREATURE_H_
#define CREATURE_H_

#include "GameObject.h"
#include "Trigger.h"
#include "Attack.h"

#include <string>
#include <iostream>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Creature : public GameObject {
 private:
  vector<string> vulnerabilities;
  Attack* attack;

 public:
  Creature(string n, string s, string d, vector<string> v, Attack* a,
	   vector<Trigger*> t);
  Creature(xml_node<>* node);
  virtual ~Creature();
  bool doAttack(string item);
  Attack* getAttack();
};
#endif
