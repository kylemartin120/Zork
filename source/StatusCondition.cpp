#include "StatusCondition.h"
#include "GameObject.h"

#include <string>
#include <iostream>

using namespace std;

StatusCondition::StatusCondition(string obj, string stat) :
  Condition(obj) {
  status = stat;
}

StatusCondition::StatusCondition(xml_node<>* node) : Condition(node) {
  status = node->first_node("status")->value();
}

StatusCondition::~StatusCondition() {}

string StatusCondition::getStatus() {
  return status;
}
