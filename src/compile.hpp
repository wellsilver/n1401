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

struct addr {
  int a;
  string name;
};

string compiletotape(string f) {
  vector<struct instruction> alli = instructionlist();
  
  string binary = "";

  string entire = "";
  string current= "";
  bool hasA = false;
  bool AisFX= false; // %FX
  bool hasB = false;
  bool hasD = false;

  while (true) {
    
  }

  std::cout << f;

  return binary;
}

#endif