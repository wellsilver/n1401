#ifndef cpi_h
#define cpi_h

#include <string>
#include "instructions.hpp"

using namespace std;

string addressfromint(int addr) {
  string ret;
  
  return ret;
}

string readuntill(char v, string *f) {
  string r = "";
  for (auto c : *f)
    if (c == '\n' || c == v) break;
    else r+=c;
  f->erase(1,r.length());
  return r;
}

string compiletocode(string f) {
  string binary;
  
  int lines = 0;
  for (auto c : f)
    if (c=='\n') lines++;
  cout << f << endl;
  bool valid = false;
  string instr = "";
  string a = "";
  bool hasa = false;
  string b = "";
  bool hasb = false;
  string d = "";
  bool hasd = false;
  vector<struct instruction> instructions = instructionlist();
  
  for (int loop=0; loop<lines;loop++) {
    hasa=false, hasb = false, hasd = false;
    instr = readuntill(',', &f);
    if (instr[instr.length()] == ':') continue;
    for (auto i : instructions) {
      if (i.name == instr && i.hasA == hasa && i.hasB == hasb && i.hasD == hasd) valid = true;
    }
    if (!valid) {
      printf("\e[31m[Error] Instruction does not exist (check its arguements) \"%s\"\n\e[0m", instr.data());
      exit(-2);
    }
  }
  
  return binary;
}

#endif