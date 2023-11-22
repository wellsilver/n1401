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

  current.name = "b"; // Branch (unconditional)
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  current.name = "b"; // Branch if indicator on
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = true;
  ret.push_back(current);
  current.name = "b"; // Branch if character equal
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = true;
  ret.push_back(current);
  current.name = "bwz"; // Branch if wordmark or zone
  current.op = "V";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = true;
  ret.push_back(current);
  current.name = "c"; // compare
  current.op = "C";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "h"; // halt
  current.op = ".";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "h"; // halt and branch
  current.op = ".";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mn"; // move numerical
  current.op = "D";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mz"; // move zone
  current.op = "Y";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "sw"; // set word mark
  current.op = ",";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "sw"; // set word mark (2)
  current.op = ",";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cw"; // clear word mark
  current.op = "q";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cw"; // clear word mark (2)
  current.op = "q";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cs"; // clear storage
  current.op = "/";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cs"; // clear storage and branch
  current.op = "/";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mcw"; // clear storage and branch
  current.op = "M";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mcs"; // move character and supress zero's
  current.op = "Z";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mce"; // move character and edit
  current.op = "E";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "lca"; // load characters to word mark
  current.op = "L";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "za"; // zero and add
  current.op = "L";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);


  return ret;
}

#endif