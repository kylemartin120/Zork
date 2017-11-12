#include "Trigger.h"
#include "Condition.h"

#include <iostream>
#include <string>

using namespace std;

Trigger::Trigger(string comms[], bool p, Condition * conds[]) {
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
  for (unsigned int i = 0; i < sizeof(conds) / sizeof(conds[0]); i++) {
    if (!conds.isTrue()) {
      return false;
    }
  }

  return true;
}

void Trigger::getCommands() {
  return commands;
}
