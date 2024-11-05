#ifndef inc
#define inc
#include <string>
#include <vector>
using namespace std;

string characters = " 1234567890#@:>√"  \
                    "¢/STUVWXYZ⧧,%='\"" \
                    "-JKLMNOPQR!$*);Δ"  \
                    "&ABCDEFGHI?.⌑(<⯒";
string bcdversion = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" \
                    "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F" \
                    "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F" \
                    "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F";

struct instruction {
  string name; // h, c, eg autocoder list
  string op;   // ".", ",", eg actual opcode that would be given to 1401
  bool hasA;
  bool AisFX; // %FX
  bool hasB;
  bool hasD;
  bool pseudo; // if an actual instruction or not
};

string lower(string v) {
  string ret;
  for (auto c : v) ret += tolower(c);
  return ret;
}

// return a list of all instructions
vector<struct instruction> instructionlist() {
  vector<struct instruction> ret;
  struct instruction current = {};

  current.name = "b"; // Branch (unconditional)
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  current.name = "b"; // Branch if indicator on
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = true;
  ret.push_back(current);
  current.name = "b"; // Branch if character equal
  current.op = "B";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = true;
  ret.push_back(current);
  current.name = "bwz"; // Branch if wordmark or zone
  current.op = "V";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = true;
  ret.push_back(current);
  current.name = "c"; // compare
  current.op = "C";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "h"; // halt
  current.op = ".";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "h"; // halt and branch
  current.op = ".";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mn"; // move numerical
  current.op = "D";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mz"; // move zone
  current.op = "Y";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "sw"; // set word mark
  current.op = ",";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "sw"; // set word mark (2)
  current.op = ",";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cw"; // clear word mark
  current.op = "q";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cw"; // clear word mark (2)
  current.op = "q";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cs"; // clear storage
  current.op = "/";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cs"; // clear storage and branch
  current.op = "/";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mcw"; // clear storage and branch
  current.op = "M";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mcs"; // move character and supress zero's
  current.op = "Z";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "mce"; // move character and edit
  current.op = "E";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "lca"; // load characters to word mark
  current.op = "L";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "za"; // zero and add
  current.op = "L";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "zs"; // zero and subtract
  current.op = "!";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "a"; // add (two fields)
  current.op = "a";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "a"; // add (one field)
  current.op = "a";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "s"; // add (two fields)
  current.op = "s";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "s"; // add (one field)
  current.op = "s";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "m"; // multiply
  current.op = "@";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "d"; // divide
  current.op = "%";
  current.hasA = true;
  current.AisFX = false;
  current.hasB = true;
  current.hasD = false;
  ret.push_back(current);
  current.name = "r"; // read a card
  current.op = "1";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "p"; // punch a card
  current.op = "4";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "ss"; // select stacker
  current.op = "k";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = true;
  ret.push_back(current);
  current.name = "w"; // write a line
  current.op = "2";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "cc"; // control carriage
  current.op = "f";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = true;
  ret.push_back(current);
  current.name = "wrp"; // write a line, read a card, punch a card
  current.op = "7";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "wr"; // write a line, read a card
  current.op = "3";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "wp"; // write a line, punch a card
  current.op = "6";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "rp"; // read a card, punch a card
  current.op = "5";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.pseudo = true;
  current.name = "card"; // pseudo
  current.op = "";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "db"; // pseudo
  current.op = "";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  current.name = "dbs"; // pseudo
  current.op = "";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  current.name = "dbe"; // pseudo
  current.op = "";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  current.name = "ptr"; // pseudo
  current.op = "";
  current.hasA = false;
  current.AisFX = false;
  current.hasB = false;
  current.hasD = false;
  ret.push_back(current);
  
// todo: http://www.bitsavers.org/pdf/ibm/1401/R29-0044-2_1401_Symbolic_Programming_System_Student_Materials.pdf page 43, will not be doing that 
// check if pseudo is true while your doing it
  return ret;
}

#endif