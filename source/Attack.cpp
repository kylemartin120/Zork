#include "Attack.h"

Attack::Attack(vector<Condition*> c, vector<string> p, vector<string> a) {
  conditions = c;
  prints = p;
  actions = a;
}

Attack::Attack(xml_node<>* node) {
  for (xml_node<>* cur_node = node->first_node("action");
       cur_node; cur_node = cur_node->next_sibling("action")) {
    actions.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("print");
       cur_node; cur_node = cur_node->next_sibling("print")) {
    prints.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("condition");
       cur_node; cur_node = cur_node->next_sibling("condition")) {
    if (cur_node->first_node("has") == NULL) {
      Condition* condition = new StatusCondition(cur_node);
      conditions.push_back(condition);
    }
    else {
      Condition* condition = new HasCondition(cur_node);
      conditions.push_back(condition);
    }
  }
}

Attack::~Attack() {}

vector<string> Attack::getPrints() {
  return prints;
}

vector<string> Attack::getActions() {
  return actions;
}
