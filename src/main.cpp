#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#include "compile.hpp"
#include "preproccess.hpp"

string format = "raw";
string output;
string input;

string help = "n1401 Assembler for the IBM 1401\n" \
              "\n\e[31m[Error] \e[93m[Warn] \e[0m\n\n" \
              "-h  - print this menu\n" \
              "-v  - print the version\n" \
              "-o  - specify an output file\n" \
              "-g  - specify a format for output file\n" \
              " ^  rawtape  write the binary as you would onto a tape - default\n";

string version = "0"; // todo

int main(int argc, char **argv) {
  for (int loop=1;loop<argc;loop++) {
    if (string(argv[loop]) == string("-h")) {
      cout << help << endl;
      return 0;
    }
    if (string(argv[loop]) == string("-v")) {
      cout << version << endl;
      return 0;
    }
    if (string(argv[loop]) == string("-o")) {
      loop++;
      if (loop < argc) {
        output = string(argv[loop]);
      }
      else {
        printf("\e[31m[Error] Empty -o arguement\n\e[0m");
        return -1;
      }
      continue;
    }
    if (string(argv[loop]) == string("-g")) {
      loop++;
      if (loop < argc) {
        format = string(argv[loop]);
      }
      else {
        printf("\e[31m[Error] Empty -g arguement\n\e[0m");
        return -1;
      }
      continue;
    }
    // else
    if (input.empty()) {
      input = string(argv[loop]);
    } else {
      printf("\e[31m[Error] Cannot have multiple input files\n\e[0m");
      return -1;
    }
  }
  if (input.empty()) {
    printf("\e[31m[Error] Cannot have no input files\n\e[0m");
    return -1;
  }
  if (output.empty()) {
    output = string("out.o");
  }
  
  FILE *inputfile = fopen(input.c_str(), "r");

  if (inputfile==NULL) {
    printf(input.c_str(),"\e[31m[Error] Cannot read file %s\n\e[0m");
    return -1;
  }

  string file;

  for (char c=0;c!=EOF;c=fgetc(inputfile)) {
    file += c;
  }

  file = preproccess(file);
  file = compiletotape(file);
  return 0;
}