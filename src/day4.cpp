#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <regex>
#include <map>
#include <array>

#include "common.hpp"

using namespace std;

list<string> read_lines(string filepath) {
  ifstream input_file;
  input_file.open(filepath, ios::in);

  // get input
  list<string> input;
  string chunk = "";
  string line;
  while (getline(input_file, line)) {
    if (line.size() <= 1) {
      input.push_back(chunk);
      chunk = "";
    } else {
      chunk += line + ' ';
    }
  }

  if (chunk.size() > 1) {
    // not a newline, add the last line
    input.push_back(chunk);
  }

  for (auto line: input) {
    cout << "l: " << line << endl;
  }

  return input;
}

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

  bool has_required_fields();
  static list<Passport *> parse_passports(list<string>);
  static Passport *parse_passport(string);

  private:

  map<string, string> fields;
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

list<Passport *> Passport::parse_passports(list<string> groups) {
  list<Passport *> passports;

  for (auto group: groups) {
    Passport *passport = parse_passport(group);
    passports.push_back(passport);
  }

  return passports;
}

Passport *Passport::parse_passport(string group) {
  Passport *passport = new Passport();

  vector<string> keypairs = split_string(group, ' ');
  for (string keypair: keypairs) {
    vector<string> keyval = split_string(keypair, ':');
    passport->fields.insert({ keyval[0], keyval[1] });
  }

  return passport;
}

int main() {
  list<string> test_input = read_lines("input/day4_test.txt");
  list<Passport *> test_passports = Passport::parse_passports(test_input);
  
  int test_valid = 0;
  for (auto pass: test_passports) {
    if (pass->has_required_fields()) {
      ++test_valid;
    }
  }
  
  cout << "test: " << test_valid << "\n";
  assert(test_valid == 2);

  list<string> in = read_lines("input/day4.txt");
  list<Passport *> passports = Passport::parse_passports(in);
  
  int valid = 0;
  for (auto pass: passports) {
    if (pass->has_required_fields()) {
      ++valid;
    }
  }
  
  cout << "Valid: " << valid << "\n";

  return 0;
}