#include "Creature.h"

Creature::Creature(string n, string s, string d, vector<string> v, Attack* a,
		   vector<Trigger*> t) : GameObject(n, d, s, t) {
  vulnerabilities = v;
  attack = a;
}

Creature::Creature(xml_node<>* node) : GameObject(node) {
  for (xml_node<>* cur_node = node->first_node("vulnerability");
       cur_node; cur_node = cur_node->next_sibling("vulnerability")) {
    vulnerabilities.push_back(cur_node->value());
  }

  if (node->first_node("attack") != NULL) {
    attack = new Attack(node->first_node("attack"));
  }

  obj_type = "creature";
}

Creature::~Creature() {}

bool Creature::doAttack(string item) {
  for (unsigned int i = 0; i < vulnerabilities.size(); i++) {
    if (vulnerabilities[i] == item) {
      return true;
    }
  }

  return false;
}

Attack* Creature::getAttack() {
  return attack;
}
