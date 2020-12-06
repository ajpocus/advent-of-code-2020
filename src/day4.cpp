#include <iostream>
#include <list>
#include <string>
#include <regex>
#include <map>

#include "common.hpp"

using namespace std;

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

  static list<Passport *> parse_input(list<string>);

  bool has_required_fields();

  private:

  map<string, string> fields;

  void parse_line(string);
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

list<Passport *> Passport::parse_input(list<string> lines) {
  Passport *current_passport = new Passport();
  list<Passport *> passports;

  for (auto line: lines) {
    if (line.size() == 0) {
      passports.push_back(current_passport);
      current_passport = new Passport();
    }

    current_passport->parse_line(line);
  }

  return passports;
}

void Passport::parse_line(string line) {
  vector<string *> pairs = split_string(line, ' ');

  map<string, string> new_fields;

  for (string *pairstr: pairs) {
    vector<string *> keyval = split_string(*pairstr, ':');
    string key = *keyval[0];
    string val = *keyval[1];
    cout << "key, val: " << key << ":" << val << "\n";
    fields.insert({ key, val });
  }
}

int main() {
  list<string> test_lines = get_file("input/day4_test.txt");
  list<Passport *> test_passports = Passport::parse_input(test_lines);
  
  int test_valid = 0;
  for (auto pass: test_passports) {
    if (pass->has_required_fields()) {
      ++test_valid;
    }
  }
  
  cout << test_valid << "\n";
  assert(test_valid == 2);

  list<string> in = get_file("input/day4.txt");
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