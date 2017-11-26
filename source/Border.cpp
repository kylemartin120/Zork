#include "Border.h"

Border::Border(string n, string d) {
  name = n;
  direction = d;
}

Border::Border(xml_node<>* node) {
  name = node->first_node("name")->value();
  direction = node->first_node("direction")->value();
}

Border::~Border() {}

string Border::getName() {
  return name;
}

string Border::getDirection() {
  return direction;
}
