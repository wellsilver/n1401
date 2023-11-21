#ifndef inh
#define inh
#include <string>
#include <vector>
using namespace std;

struct instruction {
  string name; // h, c, eg autocoder list
  string op;   // ".", ",", eg actual opcode that would be given to 1401
  bool hasA;
  bool AisFX; // %FX
  bool hasB;
  bool hasD;
};

// return a list of all instructions
vector<struct instruction> instructionlist() {
  vector<struct instruction> ret;
  struct instruction current;

  

  return ret;
}

#endif