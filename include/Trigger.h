#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Condition.h"
#include "StatusCondition.h"
#include "HasCondition.h"

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Condition;

class Trigger {
 public:
  vector<string> actions;
  vector<string> prints;
  vector<string> commands;
  bool permanent;
  bool used; // only matters if permanent is false
  vector<Condition*> conditions;

  Trigger(vector<string> a, vector<string> ps, vector<string> co, bool p,
	  vector<Condition*> c);
  Trigger(xml_node<>* node);
  virtual ~Trigger();
  vector<Condition*> getConditions();
  vector<string> getPrints();
  vector<string> getActions();
};
#endif
