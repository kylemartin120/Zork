#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Condition.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Condition;

class Trigger {
 private:
  vector<string> actions;
  vector<string> prints;
  vector<string> commands;
  bool permanent;
  bool used; // only matters if permanent is false
  vector<Condition*> conditions;

 public:
  Trigger(vector<string> a, vector<string> ps, vector<string> co, bool p,
	  vector<Condition*> c);
  virtual ~Trigger();
  bool isTriggered(string curCommand);
  vector<string> getPrints();
  vector<string> getActions();
};
#endif
