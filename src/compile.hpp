#ifndef cpi_h
#define cpi_h

#include <string>
#include "instructions.hpp"

using namespace std;

string addressfromint(int addr) {
  string ret = "000";

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
  long unsigned int a;
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
    // there might be a bug here iwth the string checking
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
  vector<struct addr> alladdr;
  string binary = "";
  unsigned int marks = 0; // so we can get the size of the binary as binary.length()-marks

  for (auto i : instr) {
    // if this is a address then handle it
    if (i[0].back() == ':') {alladdr.push_back((struct addr) {binary.length() - marks, i[0].erase(i[0].length()-1)});continue;};
    
    // with '{' represents a word mark

    for (auto c : alli) {
      if (c.name == i[0]) { // is just the one instruction
        if (i.size() > 1) 
          if (i.size() > 2); // has B
          else if (i[1][0] == 'U' || i[1][0] == 'F' || i[1][0] == 'T') {binary += "{" + c.op + '%' + i[1]; marks++;} // A is special needs
        else {binary += '{' + c.op; marks++;} // just the one instruction
      }
    }
  };
  std::cout << binary << std::endl;
  return binary;
}

#endif