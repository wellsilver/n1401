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
  int pointer = 100; // after the bootloader
  // try to figure out the address of addresses
  for (auto ins : lines) {
    if (ins[0] == string("card")) { // change offset

    }
    if (ins[0] == string("ptr")) { // write down

    }
    if (ins[0] == string("db")) { // will need to step through manually
      

    }
  }

  return binary;
}

#endif