#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<string> get_file(string filename) {
  ifstream input_file;
  input_file.open(filename, ios::in);

  // get input
  string line;
  vector<string> input;
  while (getline(input_file, line)) {
    input.push_back(line);
  }

  return input;
}
