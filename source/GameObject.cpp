#include "GameObject.h"

GameObject::GameObject(string n, string d, string s, vector<Trigger*> t) {
  name = n;
  description = d;
  status = s;
  triggers = t;
}

GameObject::GameObject(xml_node<>* node) {
  if (node->first_node() == NULL) {
    name = node->value();
  }
  else {
    name = node->first_node("name")->value();
    if (node->first_node("description") != NULL) {
      description = node->first_node("description")->value();
    }
    if (node->first_node("status") != NULL) {
      status = node->first_node("status")->value();
    }
    for (xml_node<>* cur_node = node->first_node("trigger");
	 cur_node; cur_node = cur_node->next_sibling("trigger")) {
      Trigger* this_trig = new Trigger(cur_node);
      triggers.push_back(this_trig);
    }
  }
}

GameObject::~GameObject() {}

string GameObject::getName() {
  return name;
}

void GameObject::printDescription() {
  cout << description << endl;
}

string GameObject::getStatus() {
  return status;
}
  
bool GameObject::contains(GameObject* obj) {
  return false; // a generic GameObject cannot contain another GameObject
}
