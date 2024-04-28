#ifndef cpi_h
#define cpi_h

#include <string>
#include "instructions.hpp"

using namespace std;

string addressfromint(int addr) {
  string ret;
  
  return ret;
}

string addressfromint(string addr) {
  return addressfromint(stoi(addr));
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

// split the string into instructions and their arguements
vector<vector<string>> makeinstr(string f) {
  vector<vector<string>> instr;
  bool instring=false;

  vector<string> check;
  string current= "";

  for (auto i : f) {
    if (i == '\"' && instring==false) instring=true;
    else instring=false;
    if (i == '\n') {check.insert(check.end(), current);current.clear();instr.insert(instr.end(),check);check.clear();continue;};
    if (i == ',' && instring == false)  {check.insert(check.end(), current);current.clear();continue;}
    current+=i;
  }
  return instr;
}

string compiletotape(string f) {
  vector<struct instruction> alli = instructionlist();
  vector<vector<string>> instr = makeinstr(f);
  string binary = "";

  string name;
  bool hasA;
  bool AisFX; // %FX
  bool hasB;
  bool hasD;

  for (auto x : instr) {
    /// set the booleans first
    name = x[0];
    hasA = false;
    AisFX = false;
    hasB = false;
    hasD = false;

    // does it have a? is a fx? is a d?
    if (x.size()>1) {
      if (x[1][0] == '%') { // a is fx
        AisFX = true;
      } else if (x[1][0] == 'd') {
        hasD = true;
      } else {
        hasA = true;
      }
    }
    // does it have b? is b d?
    if (x.size()>2) {
      if (x[2][0] == 'd') {
        hasD = true;
      } else {
        hasB = true;
      }
    }
    // does it have d?
    if (x.size()>3) {
      if (x[3][0] == 'd') {
        hasD = true;
      }
    }

    /// find the instruction in the instruction list then write its binary
    for (auto i : alli) if (i.name == name && i.hasA == hasA && i.hasB == hasB && i.hasD == hasD && i.AisFX == AisFX) {
      
    }
      
  }

  return binary;
}

#endif