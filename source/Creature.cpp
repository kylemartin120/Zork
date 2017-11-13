#include "Creature.h"
#include "Trigger.h"
#include "GameObject.h"
#include "Attack.h"

#include <string>
#include <iostream>
#include <vector>

Creature::Creature(string n, string s, string d, vector<string> v, Attack* a,
		   vector<Trigger*> t) : GameObject(n, d, s, t) {
  vulnerability = v;
  attack = a;
}

Creature::~Creature() {}

Attack* Creature::attack(GameObject* item) {
  cout << "You assault the " << name << " with the " << item->getName() << endl;
  for (unsigned int i = 0; i < vulnerability.size(); i++) {
    if (vulnerability[i] == item->getName()) {
      return attack;
    }
  }

  return NULL;
}
