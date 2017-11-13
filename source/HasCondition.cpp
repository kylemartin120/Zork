#include "HasCondition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

HasCondition::HasCondition(bool h, GameObject* obj, GameObject* own) :
  Condition(obj) {
  has = h;
  owner = own;
}

HasCondition::~HasCondition() {}

bool HasCondition::isTrue() {
  if (has) {
    return owner->contains(object);
  }

  return !owner->contains(object);
}
