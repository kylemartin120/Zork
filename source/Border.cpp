#include "Border.h"

#include <string>

using namespace std;

Border::Border(string n, string d) {
  name = n;
  direction = d;
}

Border::~Border() {}

string Border::getName() {
  return name;
}

string Border::getDirection() {
  return direction;
}
