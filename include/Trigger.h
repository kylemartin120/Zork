#include<iostream>
#include<string>

class Trigger {
 private:
  string commands[];
  GameObject owner;
  int status;

 public:
  string[] getCommands();
  GameObject getOwner();
  int getStatus();
}
