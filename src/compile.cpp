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
  long unsigned int a; // address
  long unsigned int r; // reference in binary
  string name;
};

// split the string into instructions and their arguements
vector<vector<string>> makeinstr(string f) {
  vector<vector<string>> ret;

  bool instring = false;
  string current;
  vector<string> next;

  for (auto c : f) {
    if (c == ',' && instring == false) {
      next.push_back(current);
      current.clear();
      continue;
    }
    if (c == '\n') {
      next.push_back(current);
      current.clear();
      ret.push_back(next);
      next.clear();
      continue;
    }
    if (c == '\"') {
      if (instring) instring = false;
      else instring = true;
      continue;
    }
    current += c;
  }

  return ret;
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
    cout << to_string(i.size()) << " ";
    for (auto k : i) cout << k;
    cout << '\n';
    // if this is a address then add its location to the list
    if (i[0].back() == ':') {
      // find where it is on alladdr and place the address there
      std::string n = i[0];
      n.erase(n.end()-1);
      for (unsigned int ialladdr=0;ialladdr<alladdr.size();ialladdr++)
        if (alladdr[ialladdr].name == n)
          alladdr[ialladdr].a = binary.size()-marks;\
    }
    
    // with '~' represents a word mark

    // get the op code, preproccessor allready checks if its valid
    for (auto c : alli) {
      if (c.name == i[0]) {
        // add instruction to binary
        if (!c.pseudo) {
          binary += "~" + c.op;
          marks++;

          // handle arguments1
          for (unsigned int d = 1;i.size()>d;d++) {
            // is fx?
            if (i[d][0] == 'U' || i[d][0] == 'T' || i[d][0] == 'F') {
              i[d].erase(i[d].begin());
              binary += i[d];
              break;
            }
            // is d character?
            if (i[d][0] == 'D') {
              i[d].erase(i[d].begin());
              break;
            }
            // is address pointer thing?
            for (unsigned int loop=0;loop<alladdr.size();loop++)
              if (alladdr[loop].name == i[d]) {
                alladdr[loop].r = binary.size();
                break;
              }
            // none of those, then its a address
            if (i[d][0] == '0' && i[d][1] == 'x') { // hex
              i[d].erase(i[d].begin(),i[d].begin()+1);
              binary += addressfromint(std::stoul(i[d], nullptr, 16));
            } else { // assuming its decimal
              binary += addressfromint(std::atoi(i[d].c_str()));
            }
          }

        } else { /// handle pseudo ops
          // db, define bytes (write raw data)
          if (c.name == "db") {
            // preproccessor is supposed to make strings one
            binary += i[1];
            continue;
          }
          // dbs, define bytes word mark at start
          if (c.name == "dbs") {
            // preproccessor is supposed to make strings one
            binary += "~";
            marks++;
            binary += i[1];
            continue;
          }
          // dbe, define bytes word mark at end
          if (c.name == "dbe") {
            // preproccessor is supposed to make strings one
            binary += i[1];
            binary.insert(binary.end()-1, '~');
            marks++;
            continue;
          }
        }

        goto finishinstruction; // instruction added to binary, we are done here
      }
    }

    finishinstruction:;
  };

  // haved to go through the list of addresses and add them
  for (auto addr : alladdr) {
    std::string thing = addressfromint(addr.a);
    binary[addr.r] = thing[0];
    binary[addr.r+1] = thing[1];
    binary[addr.r+2] = thing[2];
  }

  std::cout << binary << std::endl;
  return binary;
}

#endif