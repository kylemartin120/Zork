#include "Trigger.h"
#include "Condition.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Trigger::Trigger(vector<string> a, vector<string> pr, bool p,
		 vector<Condition*> c) {
  actions = a;
  prints = pr;
  permanent = p;
  used = false;
  conditions = c;
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

vector<string> Trigger::getPrints() {
  return prints;
}

vector<string> Trigger::getActions() {
  return actions;
}
