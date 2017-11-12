#include "GameObject.h"
#include "Trigger.h"

#include <string>
#include <iostream>

using namespace std;

GameObject::GameObject(string n, string d, string s, Trigger * t[]) {
  name = n;
  description = d;
  status = s;
  trigs = t;
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

bool testTrigs() {
  if (sizeof(trigs) == 0) {
    return false;
  }

  bool activate = false;
  
  for (unsigned int i = 0; i < sizeof(trigs) / sizeof(trigs[0]); i++) {
    if (trigs[i].isTriggered()) {
      activate = true;
      trigs[i].act();
    }
  }

  return activate;
}
  
bool contains(GameObject * obj) {
  return false; // a generic GameObject cannot contain another GameObject
}
