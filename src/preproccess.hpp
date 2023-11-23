// goal is to find any compiling errors and format to be easier to compile with
#ifndef pre_h
#define pre_h

#include "instructions.hpp"
#include <string>

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

  char stringtype;
  bool instring = false;
  bool incomment = false;
  int line = 1;
  // remove notes
  for (int loop=0;loop<a.size();loop++) {
    if (a.data()[loop] == '\n') {
      incomment = false;
      if (instring) {
        printf("\e[31m[Error] Unterminated string at line %i\n\e[0m", line);
        exit(-2);
      }
      line++;
    }
    if (a.data()[loop] == '\"') {
      if (instring && stringtype == '\"') {
        instring = false;
      } else {
        stringtype = '\"';
        instring = true;
      }
    }
    if (a.data()[loop] == '\'') {
      if (instring && stringtype == '\'') {
        instring = false;
      } else {
        stringtype = '\'';
        instring = true;
      }
    }
    if (instring) continue;
    if (a.data()[loop] == ';') {
      while (a.data()[loop] != '\n' && loop < a.size()) {
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
  for (int loop=0;loop<a.size();loop++) {
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
  string name;
  line = 0;
  // format addresses to make them easier to read and check for valid instructions
  for (int loop=0;loop<a.size();loop++) {
    if (a[loop] == '\n') {
      warnuncapitalized = true;
      warncharacter = true;
      line++;
    }
    name += a;
  }

  // add a line between address eg (string:\ndb "v")
  for (int loop=0;loop<a.size();loop++) {
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

  bool in_line = false;

  // remove multiple succeeding line separators
  for (int loop=0;loop<a.size();loop++) {
    if (a[loop] == '\n') {
      if (in_line == true) {
        a.erase(loop, 1);
        in_line = false;
      } else in_line = true;
    } else in_line = false;
  }

  // remove all spaces except for right after an instruction which is replaced with a `, check if valid instructions
  for (int loop=0;loop<a.size();loop++) {
    
  }
  
  return ret;
}

#endif