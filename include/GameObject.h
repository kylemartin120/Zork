#include<iostream>
#include<string>
using namespace std;

class GameObject {
 private:
  string name;
  string description;
  int status;
  Trigger trigs[];

 public:
  string printName();
  string printDescription();
  int getStatus();
  bool testTrigs();
}
