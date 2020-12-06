#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <list>

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

  static vector<Passport *> parse_input(vector<string>);

  map<string, string> fields;

  bool has_required_fields();
  void parse_line(string);
};

bool Passport::has_required_fields() {
  for (auto req_field: REQUIRED_FIELDS) {
    if (fields.count(req_field) == 0 && req_field != "cid") {
      return false;
    }
  }

  return true;
}

vector<Passport *> Passport::parse_input(vector<string> lines) {
  Passport *current_passport = new Passport();
  vector<Passport *> passports;

  for (auto line: lines) {
    if (line[0] == '\n') {
      passports.push_back(current_passport);
      current_passport = new Passport();
    }

    current_passport->parse_line(line);
  }

  return passports;
}

void Passport::parse_line(string line) {
  string raw = line.substr(0, line.size() - 1);
  vector<string> pairs = split_string(raw, ' ');

  map<string, string> new_fields;

  for (string pairstr: pairs) {
    vector<string> keyval = split_string(pairstr, ':');
    string key = keyval[0];
    string val = keyval[1];
    cout << "key, val: " << key << ", " << val << "\n";
    fields.insert(pair<string, string>(key, val));
  }
}

int main() {
  vector<string> test_lines = get_file("input/day4_test.txt");
  vector<Passport *> test_passports = Passport::parse_input(test_lines);
  
  int test_valid = 0;
  cout << "test passports: " << test_passports.size() << "\n";
  for (auto pass: test_passports) {
    cout << "map size: " << pass->fields.size() << "\n";
    if (pass->has_required_fields()) {
      ++test_valid;
    }
  }
  
  cout << test_valid << "\n";
  assert(test_valid == 2);

  vector<string> in = get_file("input/day4.txt");

  return 0;
}