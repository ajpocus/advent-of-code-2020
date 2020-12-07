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
  bool validate();
  string get_field(string);

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

  list<string> keypairs = split_string(group, ' ');
  for (string keypair: keypairs) {
    list<string> keyval = split_string(keypair, ':');
    string pr[2];

    int idx = 0;
    for (auto el: keyval) {
      pr[idx] = el;
      ++idx;
    }

    passport->fields[pr[0]] = pr[1];
  }

  return passport;
}

bool Passport::validate() {
  if (!has_required_fields()) {
    return false;
  }

  // byr (Birth Year) - four digits; at least 1920 and at most 2002.
  string byr = fields["byr"];
  cout << "byr: " << byr << endl;

  if (byr == "") { return false; }

  try {
    int byri = stoi(byr);
    if (byr.size() != 4 || byri < 1920 || byri > 2002) {
      return false;
    }
  } catch (...) {
    return false;
  }
  

  // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
  try {
    string iyr = fields["iyr"];
    cout << "iyr: " << iyr << endl;

    if (iyr == "") { return false; }

    int iyri = stoi(iyr);
    if (iyr.size() != 4 || iyri < 2010 || iyri > 2020) {
      return false;
    }
  } catch (...) {
    return false;
  }

  // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
  try {
    string eyr = fields["eyr"];
    cout << "eyr: " << eyr << endl;
    
    if (eyr == "") { return false; }

    int eyri = stoi(eyr);
    if (eyr.size() != 4 || eyri < 2020 || eyri > 2030) {
      return false;
    }
  } catch (...) {
    return false;
  }

  // hgt (Height) - a number followed by either cm or in:
  //     If cm, the number must be at least 150 and at most 193.
  //     If in, the number must be at least 59 and at most 76.
  try {
    const regex height_matcher("(\\d+)(cm|in)");
    string hgt = fields["hgt"];
    cout << "hgt: " << hgt << endl;
    if (hgt == "") { return false; }

    smatch matches;
    bool does_match = regex_match(hgt, matches, height_matcher);
    if (does_match) {
      string height_str = matches[1].str();
      cout << "height: " << height_str << endl;
      int height = stoi(height_str);
      string unit = matches[2].str();

      if (unit == "cm") {
        if (height < 150 || height > 193) {
          return false;
        }
      } else if (unit == "in") {
        if (height < 59 || height > 76) {
          return false;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  } catch (...) {
    return false;
  }

  // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
  const regex hcl_parser("#[0-9a-fA-F]{6}");
  string hcl = fields["hcl"];
  cout << "hcl: " << hcl << endl;

  smatch matches;
  if (!regex_match(hcl, matches, hcl_parser)) {
    return false;
  }

  // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
  const vector<string> valid_colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
  string ecl = fields["ecl"];
  bool has_color = false;
  for (auto color: valid_colors) {
    if (ecl == color) {
      has_color = true;
    }
  }

  if (!has_color) {
    return false;
  }

  // pid (Passport ID) - a nine-digit number, including leading zeroes.
  const regex passport_id_pattern("\\d{9}");
  string pid = fields["pid"];
  smatch new_matches;
  if (!regex_match(pid, new_matches, passport_id_pattern)) {
    return false;
  }

  // cid (Country ID) - ignored, missing or not.

  return true;
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
  
  cout << "Valid: " << valid << endl;

  valid = 0;
  for (auto pass: passports) {
    if (pass->validate()) {
      ++valid;
    }
  }

  cout << "Super valid: " << valid << endl;

  return 0;
}