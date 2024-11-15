#ifndef cpi_c
#define cpi_c

#include <string>
#include "instructions.cpp"

using namespace std;

string addressfromint(unsigned long long addr) {
  unsigned int c0 = addr % 10;
  unsigned int c1 = ((addr % 100) - c0) / 10;
  unsigned int c2 = ((addr % 1000) - c1 - c0) / 100;

  return std::to_string(c2) + std::to_string(c1) + std::to_string(c0);
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
    if (i == '\"' && instring==false) instring=true;
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
  vector<struct addr> future;
  string binary = "";
  unsigned int marks = 0; // so we can get the size of the binary as binary.length()-marks

  for (auto i : instr) {
    // if this is a address then add it to a list
    if (i[0].back() == ':') {alladdr.push_back((struct addr) {binary.length() - marks, i[0].erase(i[0].length()-1)});continue;};
    
    // with '{' represents a word mark

    // get the op code, and dont check if its actually valid because instructions.hpp is wrong
    for (auto c : alli) {
      if (c.name == i[0]) {
        // add instruction to binary
        if (!c.pseudo) {
          binary += "{" + c.op;
          marks++;

        } else { /// handle pseudo ops
          // db, define bytes (write raw data)
          if (c.name == "db") {
            // preproccessor is supposed to make strings one
            // trim ""
            i[1].erase(i[1].begin());
            i[1].erase(i[1].end()-1);
            binary += i[1];
          }
          // dbs, define bytes word mark at start
          if (c.name == "dbs") {
            // preproccessor is supposed to make strings one
            // trim ""
            binary += "{";
            marks++;
            i[1].erase(i[1].begin());
            i[1].erase(i[1].end()-1);
            binary += i[1];
          }
          // dbe, define bytes word mark at end
          if (c.name == "dbe") {
            // preproccessor is supposed to make strings one
            // trim ""
            i[1].erase(i[1].begin());
            i[1].erase(i[1].end()-1);
            binary += i[1];
            binary.insert(binary.end()-1, '{');
            marks++;
          }
        }
        
        /// compile specific instruction
        // handle A
        if (i.size() > 1) {
          if (i[1][0] == '0' && i[1][1] == 'x') { // hex
            i[1].erase(i[1].begin());
            i[1].erase(i[1].begin());
            binary += addressfromint(std::stoul(i[1], nullptr, 16));
          } else { // assuming its decimal
            binary += addressfromint(std::atoi(i[1].c_str()));
          }
          // handle B
          if (i.size() > 2) {
            if (i[1][0] == '0' && i[1][1] == 'x') { // hex
              i[2].erase(i[2].begin());
              i[2].erase(i[2].begin());
              binary += addressfromint(std::stoul(i[2], nullptr, 16));
            } else { // assuming its decimal
              binary += addressfromint(std::atoi(i[2].c_str()));
            }
            // can only be d left now
            if (i.size() > 3) {
              binary += i[3][0];
            }
          }
        }

        goto finishinstruction; // instruction added to binary, we are done here
      }
    }

    finishinstruction:;
  };
  std::cout << binary << std::endl;
  return binary;
}

#endif