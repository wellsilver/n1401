// goal is to find any compiling errors and format to be easier to compile with
#ifndef pre_h
#define pre_h

#include "instructions.hpp"
#include <string>
#include <iostream>

using namespace std;

string tobcd(string a) {
  string characters = " 1234567890#@:>√"  \
                      "¢/STUVWXYZ⧧,%='\"" \
                      "-JKLMNOPQR!$*);Δ"  \
                      "&ABCDEFGHI?.q(<⯒";
  string bcdversion = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" \
                      "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F" \
                      "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
                      "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";
  string ret;
  for (auto c : a) ret += bcdversion[characters.find(c)];
  return ret;
}

// todo compile all the for loops into one for loop
string preproccess(string a) {
  string ret;

  int line = 1;
  bool instring = false;
  char stringtype;

  a+='\n';
  // check for unterminated strings
  for (auto i : a) {
    if (i == '\n') {
      if (instring) {
        printf("\e[31m[Error] Unterminated string. line %i \e[0m\n", line);
        exit(-2);
      }
      line++;
    }
    if (i == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (i == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
  }
  a.erase(a.length()-1, 1);

  bool incomment = false;
  // remove notes
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == '\n') {
      incomment = false;
      line++;
    }
    if (a[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
    if (instring) continue;
    if (a[loop] == ';') {
      while (a[loop] != '\n' && loop < a.size()) {
        a.erase(loop, 1);
      }
      line++;
    }
  }


  // bcdversion[x] is the bcd version of validcharacters[x]
  string characters = " 1234567890#@:>√"  \
                      "¢/STUVWXYZ⧧,%='\"" \
                      "-JKLMNOPQR!$*);Δ"  \
                      "&ABCDEFGHI?.⌑(<⯒";
  string bcdversion = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" \
                      "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F" \
                      "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
                      "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";
  
  bool warncharacter = true;
  bool warnuncapitalized = true;

  line = 1;
  // check if strings are valid
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == '\n') {
      warnuncapitalized = true;
      warncharacter = true;
      line++;
    }
    if (a[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
    if (instring) {
      if (a[loop] >= 'a' && a[loop] <= 'z') {
        if (warnuncapitalized) {
          printf("\e[93m[Warn] Uncapitalized characters were capitalized automatically. Line %i \e[0m\n", line);
        }
        warnuncapitalized = false;
        a[loop] = toupper(a[loop]);
        continue;
      }
      if (characters.find(a[loop]) == -1) {
        if (warncharacter) {
          printf("\e[93m[Warn] Character \"%c\" does not exist in 1401bcd, it has been set to \".\" Line %i \e[0m\n", a[loop], line);
        }
        warncharacter = false;
        a[loop] = '.';
      }
    }
  }

  // add a line between address eg (string:\ndb "v")
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
    if (instring) continue;
    if (a[loop] == ':') {
      a.insert(loop+1, 1, '\n');
      loop++;
    }
  }

  // remove multiple succeeding line separators
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == '\n' && a[loop+1] == '\n') {
      a.erase(loop, 1);
      loop = 0;
    }
  }

  // remove multiple succeeding spaces
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
    if (a[loop] == ' ' && a[loop+1] == ' ' && !instring) {
      a.erase(loop, 1);
      loop = 0;
    }
  }

  // remove ' ' from beggining of line
  bool aftern = true;
  for (int loop=1;loop<a.size()-1;loop++) {
    if (a[loop] == ' ' && aftern)
      a.erase(loop, 1);
    aftern = false;
    if (a[loop] == '\n')
      aftern = true;
  } 

  aftern = true;
  for (int loop=a.size()-1;loop>0;loop--) {
    if (a[loop] == ' ' && aftern)
      a.erase(loop, 1);
    aftern = false;
    if (a[loop] == '\n')
      aftern = true;
  }

  vector<struct instruction> instructions = instructionlist();
  string instr = "";
  bool nextn = false;
  bool isinst = false;
  line = 1;

  // check for valid instructions and place a comma after the instructions
  for (int loop=1;loop<a.size();loop++) {
    if (nextn && a[loop] == '\n') {
      nextn = false;
      continue;
    } else if (nextn) continue;

    if (a[loop] == ':') { // check if the address is valid
      for (auto i : instr) {// check if in valid alphanumeric range a-z
        if (!(tolower(i) >= 'a' && tolower(i) <= 'z')) isinst = true;
      }
      if (isinst) {
        printf("\e[31m[Error] Addresses can only be named a-z not \"%s\"\n\e[0m", instr.data());
        exit(-2);
      }
      isinst = false;
      instr = "";
      nextn = true;
      line++;
      loop--;
      continue;
    }
    if (a[loop] == ' ' || a[loop] == '\n') {
      for (auto i : instructions) // set isinst if instr is a instruction
        if (i.name == instr) isinst = true;

      if (!isinst) {
        printf("\e[31m[Error] Expected an instruction, got \"%s\"\n\e[0m", instr.data());
        exit(-2);
      }
      if (a[loop] == ' ') a[loop] = ',';
      isinst=false;
      instr = "";
      nextn = true;
      line++;
      loop--;
      continue;
    }
    instr += a[loop];
  }

  instring = false;

  for (int loop=1;loop<a.size();loop++) {
    if (a[loop] == ' ' && !instring) 
      a.erase(loop,1);

    if (a[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
  }

  return a;
}

#endif