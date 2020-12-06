#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <regex>
#include <map>
#include <array>

#include "common.hpp"

using namespace std;

string read_entire_file(string filepath) {
  ifstream input_file;
  input_file.open(filepath, ios::in);

  // get input
  string input;
  string line;
  while (getline(input_file, line)) {
    input += line + '\n';
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
  static list<Passport *> parse_passports(string);
  static list<string> parse_lines(string input);
  static list<string> parse_groups(list<string>);
  static list< vector<string> > parse_keypairs(string);
  static Passport *parse_passport(list< vector<string> >);

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

list<Passport *> Passport::parse_passports(string input) {
  list<Passport *> passports;

  list<string> lines = parse_lines(input);
  list<string> groups = parse_groups(lines);
  for (auto group: groups) {
    list<vector<string>> keypairs = parse_keypairs(group);
    Passport *passport = parse_passport(keypairs);
    passports.push_back(passport);
  }

  return passports;
}

list<string> Passport::parse_lines(string input) {
  list<string> lines;

  const regex line_parser("(.*?\n)+");
  smatch matches;
  regex_search(input, matches, line_parser);

  for (auto match: matches) {
    if (match == *matches.begin()) {
      continue;
    }

    string match_str = match.str();
    lines.push_back(match_str.substr(0, match_str.size() - 1));
  }

  return lines;
};

list<string> Passport::parse_groups(list<string> lines) {
  list<string> groups;
  string current_group = "";

  for (auto line: lines) {
    // if it has a newline or is blank
    size_t len = line.size();
    if (len <= 1) {
      groups.push_back(current_group);
      current_group = "";
    } else {
      current_group += line.substr(0, len - 1) + ' ';
    }
  }

  if (current_group.size() > 1) {
    lines.push_back(current_group);
  }

  cout << "groups; " << groups.size() << endl;

  return lines;
}

list< vector<string> > Passport::parse_keypairs(string group) {
  list< vector<string> > keypairs = {};

  const regex keypair_regex("((\\w+):(.+?)\\s)+");
  smatch matches;
  vector<string> keypair;

  regex_search(group, matches, keypair_regex);

  for (smatch::const_iterator it = matches.begin(); it != matches.end(); ++it) {
    long idx = it - matches.begin();
    if (idx == 0) { continue; }

    switch (idx % 3) {
      case 1:
        // whole group match, skip
        break;
      case 2:
        // key match
        cout << "key: " << *it << endl;
        break;
      case 3:
        // val match
        cout << "val: " << *it << endl;
        break;
      default:
        break;
    }
  }

  // TODO finish this function

  return keypairs;
}

Passport *parse_passport(list< vector<string> > pairs) {
  Passport *passport = new Passport();

  // TODO; fill in the details

  return passport;
}

int main() {
  string test_input = read_entire_file("input/day4_test.txt");
  list<Passport *> test_passports = Passport::parse_passports(test_input);
  
  int test_valid = 0;
  for (auto pass: test_passports) {
    if (pass->has_required_fields()) {
      ++test_valid;
    }
  }
  
  cout << "test: " << test_valid << "\n";
  assert(test_valid == 2);

  string in = read_entire_file("input/day4.txt");
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