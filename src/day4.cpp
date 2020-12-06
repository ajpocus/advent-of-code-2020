#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <regex>
#include <map>

#include "common.hpp"

using namespace std;

string read_entire_file(string filepath) {
  ifstream input_file;
  input_file.open(filepath, ios::in);

  // get input
  string input;
  string line;
  while (getline(input_file, line)) {
    input += line;
  }

  return input;
}

const regex passport_parser = "((\\w+):(.+?))";

const string REQUIRED_FIELDS[] {
  "byr",
  "iyr",
  "eyr",
  "hgt",
  "hcl",
  "ecl",
  "pid",
  "cid"
};

class Passport {
  public:

  static list<Passport *> parse_input(string);

  bool has_required_fields();

  private:

  map<string, string> fields;

  static Passport *parse_single(string);
};

bool Passport::has_required_fields() {
  if (fields.size() < 5) {
    return false;
  }

  for (auto key: REQUIRED_FIELDS) {
    if (fields.count(key) == 0 && key != "cid") {
      return false;
    }
  }

  return true;
}

list<Passport *> Passport::parse_input(string raw_input) {
  string current_str = "";
  list<string> passport_strings;

  for (string::iterator it = raw_input.begin(); it != raw_input.end(); ++it) {
    cout << "it: " << *it << "\n";
    if (*it == '\n' && *(next(it)) == '\n') {
      cout << "aokesjofwijefoij" << *(next(it)) << "\n";
      passport_strings.push_back(current_str);
      current_str = "";
      ++it;
      cout << "newline handler: [" << *it << "]\n";
    } else if (isspace(*it)) {
      cout << "this ain't no ordinary gun\n";
      current_str.push_back(' ');
    } else {
      current_str.push_back(*it);
    }
  }

  if (current_str.size() > 0) {
    passport_strings.push_back(current_str);
  }

  // testing logs
  for (auto str: passport_strings) {
    cout << "str: " << str << "\n";
  }

  list<Passport *> passports;
  for (auto pass_str: passport_strings) {
    passports.push_back(Passport::parse_single(pass_str));
  }

  return passports;
}

Passport *Passport::parse_single(string line) {
  vector<string *> pairs = split_string(line, ' ');

  map<string, string> new_fields;

  for (string *pairstr: pairs) {
    vector<string *> keyval = split_string(*pairstr, ':');
    string key = *keyval[0];
    string val = *keyval[1];
    cout << "key, val: " << key << ":" << val << "\n";
    new_fields.insert({ key, val });
  }

  Passport *passport = new Passport();
  passport->fields = new_fields;

  return passport;
}

int main() {
  string test_input = read_entire_file("input/day4_test.txt");
  list<Passport *> test_passports = Passport::parse_input(test_input);
  
  int test_valid = 0;
  for (auto pass: test_passports) {
    if (pass->has_required_fields()) {
      ++test_valid;
    }
  }
  
  cout << "test: " << test_valid << "\n";
  assert(test_valid == 2);

  string in = read_entire_file("input/day4.txt");
  list<Passport *> passports = Passport::parse_input(in);
  
  int valid = 0;
  for (auto pass: passports) {
    if (pass->has_required_fields()) {
      ++valid;
    }
  }
  
  cout << "Valid: " << valid << "\n";

  return 0;
}