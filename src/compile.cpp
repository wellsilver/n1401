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
  vector<std::string> addrstrlist; // dont compile gotohere: as if its a integer
  string binary = "";
  unsigned int marks = 0; // so we can get the size of the binary as binary.length()-marks

  // get all addresses
  for (auto i : instr)
    if (i[0].back() == ':') {
      alladdr.push_back({.name=i[0]});
      alladdr.back().name.erase(alladdr.back().name.end()-1); // get the : at the end of them off
    }

  for (auto i : instr) {
    // if this is a address then add its location to the list
    if (i[0].back() == ':') {
      // find where it is on alladdr and place the address there
      
    }
    
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
            continue;
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
            continue;
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
            continue;
          }
        }
        
        // handle arguments
        for (unsigned int d = 1;i.size()>d;d++) {
          // is fx?
          if (i[d][0] == 'U' || i[d][0] == 'T' || i[d][0] == 'F') {
            i[d].erase(i[d].begin());
            binary += i[d];
            continue;
          }
          // is d character?
          if (i[d][0] == 'D') {
            i[d].erase(i[d].begin());
          }
          // none of those, then its a address
          if (i[d][0] == '0' && i[d][1] == 'x') { // hex
            i[d].erase(i[d].begin(),i[d].begin()+1);
            binary += addressfromint(std::stoul(i[d], nullptr, 16));
          } else { // assuming its decimal
            binary += addressfromint(std::atoi(i[d].c_str()));
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