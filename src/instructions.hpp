#ifndef inh
#define inh
#include <string>
#include <vector>
using namespace std;

struct instruction {
  string name; // h, c, eg
  string op;   // ".", ",", eg
  bool hasA;
  bool AisFX; // %FX
  bool hasB;
  bool hasD;
};

vector<struct instruction> instructionlist() {
  vector<struct instruction> ret;
  struct instruction current;

  

  return ret;
}

#endif