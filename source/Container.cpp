#include "Container.h"

Container::Container(string n, string s, string d, vector<string> a,
		     vector<string> i, vector<Trigger*> t) :
  GameObject(n, d, s, t) {
  accept = a;
  items = i;
  isOpened = false;
}

Container::Container(xml_node<>* node) : GameObject(node) {
  for (xml_node<>* cur_node = node->first_node("accept");
       cur_node; cur_node = cur_node->next_sibling("accept")) {
    accept.push_back(cur_node->value());
  }

  if (accept.size() > 0) {
    isOpened = false;
  }
  else {
    isOpened = true;
  }

  for (xml_node<>* cur_node = node->first_node("item");
       cur_node; cur_node = cur_node->next_sibling("item")) {
    items.push_back(cur_node->value());
  }
}

Container::~Container() {}

void Container::open() {
  cout << name << " contains ";
  for (unsigned int i = 0; i < items.size(); i++) {
    cout << items[i];
    if (i < items.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
  isOpened = true;
}

vector<string> Container::getItems() {
  return items;
}

bool Container::isOpen() {
  return isOpened;
}

bool Container::putItem(string item) {
  if (isOpened) {
    items.push_back(item);
    return true;
  }

  return false;
}

bool Container::contains(string item) {
  for (int i = 0; i < items.size(); i++) {
    if (items[i] == item) {
      return true;
    }
  }

  return false;
}
