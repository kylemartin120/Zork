#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Condition.h"

#include <iostream>
#include <string>

using namespace std;

class Trigger {
 private:
  string commands[];
  bool permanent;
  bool used; // only matters if permanent is false
  Condition * conditions[];

 public:
  Trigger(string comms[], bool p, Condition * conds[]);
  virtual ~Trigger();
  bool isTriggered();
  string[] getCommands();
}
#endif
