#ifndef ATTACK_H_
#define ATTACK_H_

#include "Condition.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Attack {
 private:
  vector<Condition*> conditions;
  vector<string> prints;
  vector<string> actions;

 public:
  Attack(vector<Condition*> c, vector<string> p, vector<string> a);
  virtual ~Attack();
  vector<string> getPrints();
  vector<string> getActions();
};
#endif
