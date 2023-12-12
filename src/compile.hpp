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

string tapebootloader = ""\
                        ""\
                        ""\
                        ""\
                        ""\
                        "";

string compiletotape(string f) {
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
  int prgmsize = 80; // after the bootloader
  bool warnreversecard = true;
  vector<string> ins;
  // try to figure out the address of addresses
  for (int loop=0;loop<lines.size();loop++) {
    ins = lines[loop];

    if (ins[0] == string("card")) { // change offset
      int save = prgmsize;
      if (ins.size()>1) {
        if (atoi(ins[1].c_str()) == 0) 
          prgmsize = 0;
        else
          prgmsize = atoi(ins[1].c_str())*80; // math
      }
      if (prgmsize < save && warnreversecard) {
        warnreversecard = false;
        printf("\e[31m[Warn] Cards are in reverse order, might cause overwriting\n");
      }
      continue;
    }
    if (ins[0] == string("ptr")) { // write down
      addr.push_back({prgmsize, ins[1]});
      continue;
    }
    if (ins[0] == string("db")) { // this will format db's arguements to have the string at x[1] be the data. and increment prgmsize
      string d = "";
      bool past=false;
      for (auto l : ins) {
        if (!past) {past=true;continue;} // what? are we time travelling?
        for (auto b : l) {
          if (b != '\"' && b != '<' && b != '>') prgmsize++;
          if (b != '\"') d += b;
        }
      }
      lines[loop][1] = d;
      continue;
    }
    prgmsize += 1; // instruction
    for (auto l : ins) { // catch d character, everything else is 3
      if (l.size() == 1) prgmsize += 1; // caught d character
      else prgmsize += 3; // everything else is 3 character
    }
  }
  
  binary += tapebootloader;

  // might be able to compile now?
  for (auto i : ins) {
    binary += i;
  }

  return binary;
}

#endif