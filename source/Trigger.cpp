#include "Trigger.h"
#include "Condition.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Trigger::Trigger(vector<string> a, vector<string> pr, vector<string> co,
		 bool p, vector<Condition*> c) {
  actions = a;
  prints = pr;
  commands = co;
  permanent = p;
  used = false;
  conditions = c;
}

Trigger::~Trigger(string curCommand) {}

bool Trigger::isTriggered() {
  if (used && !permanent) {
    return false;
  }
  for (unsigned int i = 0; i < conditions.size(); i++) {
    if (!conditions[i]->isTrue()) {
      return false;
    }
  }
  if (commands.size() > 0) {
    for (unsigned int i = 0; i < commands.size(); i++) {
      if (curCommand == commands[i]) {
	  used = true;
	  return true;
	  }
    }
  }
  else {
    used = true;
    return true;
  }

  return false;
}

vector<string> Trigger::getPrints() {
  return prints;
}

vector<string> Trigger::getActions() {
  return actions;
}
