#include "Condition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

Condition::Condition(GameObject* obj) {
  object = obj;
}

Condition::~Condition() {}

bool Condition::isTrue() {
  return false; // will be overwritten by other classes
}
