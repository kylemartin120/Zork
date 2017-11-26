#include "Trigger.h"

Trigger::Trigger(vector<string> a, vector<string> pr, vector<string> co,
		 bool p, vector<Condition*> c) {
  actions = a;
  prints = pr;
  commands = co;
  permanent = p;
  used = false;
  conditions = c;
}

Trigger::Trigger(xml_node<>* node) {
  used = false;
  
  if (node->first_node("type") != NULL &&
      node->first_node("type")->value() == "permanent") {
    permanent = true;
  }
  else {
    permanent = false;
  }
  
  for (xml_node<>* cur_node = node->first_node("condition");
       cur_node; cur_node = cur_node->next_sibling("condition")) {
    if (cur_node->first_node("has") == NULL) {
      StatusCondition* condition = new StatusCondition(cur_node);
      conditions.push_back(condition);
    }
    else {
      HasCondition* condition = new HasCondition(cur_node);
      conditions.push_back(condition);
    }
  }

  for (xml_node<>* cur_node = node->first_node("print");
       cur_node; cur_node = cur_node->next_sibling("print")) {
    prints.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("action");
       cur_node; cur_node = cur_node->next_sibling("action")) {
    actions.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("command");
       cur_node; cur_node = cur_node->next_sibling("command")) {
    commands.push_back(cur_node->value());
  }
}

Trigger::~Trigger() {}

vector<Condition*> Trigger::getConditions() {
  return conditions;
}

vector<string> Trigger::getPrints() {
  return prints;
}

vector<string> Trigger::getActions() {
  return actions;
}
