#include "HasCondition.h"

using namespace std;

HasCondition::HasCondition(bool h, string obj, string own) :
  Condition(obj) {
  has = h;
  owner = own;
}

HasCondition::HasCondition(xml_node<>* node) : Condition(node) {
  if ((string) node->first_node("has")->value() == "yes") {
    has = true;
  }
  else {
    has = false;
  }
  
  owner = node->first_node("owner")->value();
}

HasCondition::~HasCondition() {}

bool HasCondition::hasType() {
  return true;
}

bool HasCondition::getHas() {
  return has;
}

string HasCondition::getOwner() {
  return owner;
}
