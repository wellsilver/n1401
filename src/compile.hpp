#ifndef cpi_h
#define cpi_h

#include <string>
#include "instructions.hpp"

using namespace std;

string addressfromint(int addr) {
  string ret = "000";

  ret[2] = addr%10; // get the first digit (from the right)
  ret[1] = (addr%100 - addr%10); // get the second digit (from the right)
  if (addr >= 1000) { // get the third digit (from the right)
    
  } else ret[0] = addr%1000 - addr%100 - addr%10;

  return ret;
}

string addressfromint(string addr) {
  return addressfromint(std::atoi(addr.c_str()));
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

  // holy shit this is scary
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

  unsigned int offset = 0;
  
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
    else if (x.size()>2) {
      if (x[2][0] == 'd') {
        hasD = true;
      } else {
        hasB = true;
      }
    }
    // does it have d?
    else if (x.size()>3) {
      if (x[3][0] == 'd') {
        hasD = true;
      }
    }
    std::cout << name << std::endl;
 
    /// find the instruction in the instruction list then write its binary
    for (auto i : alli) {
      if (i.name == name && i.hasA == hasA && i.hasB == hasB && i.hasD == hasD && i.AisFX == AisFX) {
        // according to the docs { is the character for word mark
        binary += "{"; // add mark so the command is executable
        binary += i.op;
        if (i.AisFX) {
          binary += std::string("%F") + x[1][1];
        } else if (i.hasA) {
          binary += addressfromint(x[1]);
        }
        if (i.hasB) {
          binary += addressfromint(x[2]);
        }
        // data here
      }
    }
  }
  return binary;
}

#endif