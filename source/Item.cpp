#include "Item.h"

Item::Item(string n, string s, string d, string w, vector<string> p,
	   vector<string> a, vector<Trigger*> t) : GameObject(n, d, s, t) {
  writing = w;
  prints = p;
  actions = a;
}

Item::Item(xml_node<>* node) : GameObject(node) {
  if (node->first_node("writing") != NULL) {
    writing = node->first_node("writing")->value();
  }

  for (xml_node<>* cur_node = node->first_node("action");
       cur_node; cur_node = cur_node->next_sibling("action")) {
    actions.push_back(cur_node->value());
  }

  for (xml_node<>* cur_node = node->first_node("print");
       cur_node; cur_node = cur_node->next_sibling("print")) {
    prints.push_back(cur_node->value());
  }
}

Item::~Item() {}

void Item::printWriting() {
  cout << writing << endl;
}

vector<string> Item::getPrints() {
  return prints;
}

vector<string> Item::getActions() {
  return actions;
}
