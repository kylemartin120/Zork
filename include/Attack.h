#ifndef ATTACK_H_
#define ATTACK_H_

#include "Condition.h"
#include "StatusCondition.h"
#include "HasCondition.h"

#include <string>
#include <iostream>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Attack {
 private:
  vector<Condition*> conditions;
  vector<string> prints;
  vector<string> actions;

 public:
  Attack(vector<Condition*> c, vector<string> p, vector<string> a);
  Attack(xml_node<>* node);
  virtual ~Attack();
  vector<string> getPrints();
  vector<string> getActions();
};
#endif
