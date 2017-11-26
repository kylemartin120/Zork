#include "Condition.h"

Condition::Condition(string obj) {
  object = obj;
}

Condition::Condition(xml_node<>* node) {
  object = node->first_node("object")->value();
}

Condition::~Condition() {}

string Condition::getObject() {
  return object;
}
