#include "Attack.h"
#include "Condition.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

Attack::Attack(vector<Condition*> c, vector<string> p, vector<string> a) {
  conditions = c;
  prints = p;
  actions = a;
}

Attack::~Attack() {}

vector<string> Attack::getPrints() {
  return prints;
}

vector<string> Attack::getActions() {
  return actions;
}
