#include "Trigger.h"
#include "Condition.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Trigger::Trigger(vector<string> comms, bool p, vector<Condition*> conds) {
  commands = comms;
  permanent = p;
  used = false;
  conditions = conds;
}

Trigger::~Trigger() {}

bool Trigger::isTriggered() {
  if (used && !permanent) {
    return false;
  }
  for (unsigned int i = 0; i < conditions.size(); i++) {
    if (!conditions[i]->isTrue()) {
      return false;
    }
  }

  used = true;
  return true;
}

vector<string> Trigger::getCommands() {
  return commands;
}
