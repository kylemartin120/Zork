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
  vector<string> commands;
  bool permanent;
  bool used; // only matters if permanent is false
  vector<Condition*> conditions;

 public:
  Trigger(vector<string> comms, bool p, vector<Condition*> conds);
  virtual ~Trigger();
  bool isTriggered();
  vector<string> getCommands();
};
#endif
