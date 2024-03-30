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
  string binary = "";
  bool instr = false;
  string c = "";
  for (auto i : f) {
    if (i != '\n') {c+=i;continue;};
    cout << c << endl;
    c.clear();
  }
  return binary;
}

#endif