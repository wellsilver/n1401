#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "address.hpp"

vector<string> output;
string format = "txt";
string input;

int main(int argc, char **argv) {
  for (int l=0;l < argc;l++) {
    cout << argv[l];
  }
  return 0;
}