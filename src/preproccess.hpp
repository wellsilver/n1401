// goal is to find any compiling errors and format to be easier to compile with
#ifndef pre_h
#define pre_h

#include <string>

using namespace std;

string preproccess(string a) {
  string ret;

  char stringtype;
  bool instring = false;
  bool incomment = false;
  int line = 0;
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
    }
  }
  cout << a;

  return ret;
}

#endif