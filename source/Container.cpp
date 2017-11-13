#include "Container.h"
#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>
#include <vector>

Container::Container(string n, string s, string d, vector<string> a,
		     vector<GameObject*> i, vector<Trigger*> t) :
  GameObject(n, d, s, t) {
  accept = a;
  items = i;
  isOpen = false;
}

Container::~Container() {}

void Container::open() {
  cout << name << " contains ";
  for (unsigned int i = 0; i < items.size(); i++) {
    cout << items[i]->getName();
    if (i < items.size() - 1) {
      cout << ", ";
    }
  }
  cout << endl;
  isOpen = true;
}

GameObject* getItem(string name) {
  if (isOpen) {
    for (unsigned int i = 0; i < items.size(); i++) {
      if (items[i]->getName() == name) {
	return items[i];
      }
    }
  }

  return NULL;
}

bool putItem(GameObject* item) {
  if (isOpen) {
    items.push_back(item);
    return true;
  }

  return false;
}
