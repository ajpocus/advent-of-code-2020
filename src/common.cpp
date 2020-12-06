#include <list>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

list<string> get_file(string filename) {
  ifstream input_file;
  input_file.open(filename, ios::in);

  // get input
  string line;
  list<string> input;
  while (getline(input_file, line)) {
    input.push_back(line);
  }

  return input;
}

vector<string> split_string(string str, char delimiter) {
  string current_token = "";
  vector<string> tokens = {};

  for (auto ch: str) {
    if (ch == delimiter) {
      tokens.push_back(current_token);
      current_token = "";
    } else {
      current_token.push_back(ch);
    }
  }

  return tokens;
}