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

string compiletocode(string f) {
  string binary;

  vector<vector<string>> lines;
  string arg = "";
  vector<string> args;

  f+='\n';
  for (auto c : f) {
    if (c == ':') {
      args = {"ptr", arg};
      lines.push_back(args);
      arg = "";
      continue;
    }
    if (c == '\n') {
      args.push_back(arg);
      if (arg != "")
        lines.push_back(args);
      args.clear();
      arg = "";
      continue;
    }
    if (c == ',') {
      args.push_back(arg);
      arg = "";
      continue;
    }
    arg += c;
  }

  vector<struct instruction> instructions = instructionlist();
  vector<struct addr> addr;
  int pointer = 0; // after the bootloader
  bool warnreversecard = true;
  vector<string> ins;
  // try to figure out the address of addresses
  for (int loop=0;loop<lines.size();loop++) {
    ins = lines[loop];

    if (ins[0] == string("card")) { // change offset
      int save = pointer;
      if (ins.size()>1) {
        if (atoi(ins[1].c_str()) == 0) 
          pointer = 0;
        else
          pointer = atoi(ins[1].c_str())*80; // math
      }
      if (pointer < save && warnreversecard) {
        warnreversecard = false;
        printf("\e[31m[Warn] Cards are in reverse order, might cause overwriting\n");
      }
      continue;
    }
    if (ins[0] == string("ptr")) { // write down
      addr.push_back({pointer, ins[1]});
      continue;
    }
    if (ins[0] == string("db")) { // this will format db's arguements to have the string at x[1] be the data. and increment pointer
      string d = "";
      bool past=false;
      for (auto l : ins) {
        if (!past) {past=true;continue;} // what? are we time travelling?
        for (auto b : l) {
          if (b != '\"' && b != '<' && b != '>') pointer++;
          if (b != '\"') d += b;
        }
      }
      lines[loop][1] = d;
      continue;
    }
    pointer += 1; // instruction
    for (auto l : ins) { // catch d character, everything else is 3
      if (l.size() == 1) pointer += 1;
      else pointer += 3;
    }
  }
  
  return binary;
}

#endif