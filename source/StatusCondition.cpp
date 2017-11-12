#include "StatusCondition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

StatusCondition::StatusCondition(GameObject * obj, string stat) {
  Condition(obj);
  status = stat;
}

StatusCondition::~StatusCondition() {}

bool StatusCondition::isTrue() {
  return (obj.getStatus() == status);
}
