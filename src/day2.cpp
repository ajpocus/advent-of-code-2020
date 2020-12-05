#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

regex parser_regex("(\\d+)-(\\d+) (\\w): (\\w+)");

int count_passwords(vector<string> input) {
  int cnt = 0;

  for (string line: input) {
    smatch matches;
    regex_match(line, matches, parser_regex);
    int lower_bound = stoi(matches[1]);
    int upper_bound = stoi(matches[2]);
    string chr = matches[3];
    string pass = matches[4];

    size_t char_count = count(pass.begin(), pass.end(), chr[0]);
    if (char_count >= lower_bound && char_count <= upper_bound) {
      ++cnt;
    }
  }

  return cnt;
}

int valid_pass_chars(vector<string> input) {
  int cnt = 0;

  for (string line: input) {
    smatch matches;
    regex_match(line, matches, parser_regex);
    int idx1 = stoi(matches[1]) - 1;
    int idx2 = stoi(matches[2]) - 1;
    string chr_str = matches[3];
    char chr = chr_str[0];
    string pass = matches[4];

    char first_char = pass[idx1];
    char other_char = pass[idx2];

    if (!(first_char == chr && other_char == chr) && ((first_char == chr && other_char != chr) || (first_char != chr && other_char == chr))) {
      ++cnt;
    }
  }

  return cnt;
}

int main() {
  vector<string> test_input_vec;
  test_input_vec.push_back("1-3 a: abcde");
  test_input_vec.push_back("1-3 b: cdefg");
  test_input_vec.push_back("2-9 c: ccccccccc");

  int test_count = count_passwords(test_input_vec);
  assert(test_count == 2);

  ifstream input_file;
  input_file.open("input/day2.txt", ios::in);

  // get input
  string line;
  vector<string> input;
  while (getline(input_file, line)) {
    input.push_back(line);
  }

  int valid_count = count_passwords(input);
  cout << valid_count << "\n";

  int test_valid_count = valid_pass_chars(test_input_vec);
  assert(test_valid_count == 1);

  int new_valid_count = valid_pass_chars(input);
  cout << new_valid_count << "\n";

  return 0;
}