#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "address.hpp"

vector<string> output;
string format = "raw";
string input;

string help = "n1401 v \n" \
              "Assembler for the IBM 1401\n"; // todo

int main(int argc, char **argv) {
  for (int loop=0;loop<argc;loop++) {
    if (string(argv[loop]) == string("-h")) {
      cout << help;
    }
  }
  return 0;
}