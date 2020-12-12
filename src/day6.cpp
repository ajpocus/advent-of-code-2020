#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using std::string;
using std::ifstream;
using std::list;
using std::cout;
using std::endl;
using std::map;

int get_yes_counts(string filepath) {
  ifstream ifs;
  ifs.open(filepath, std::ios::in);
  list< list<string> > groups;
  list<string> current_group;
  string line;

  while (getline(ifs, line)) {
    if (line == "") {
      groups.push_back(current_group);
      current_group.clear();
    } else {
      current_group.push_back(line);
    }
  }

  if (!current_group.empty()) {
    groups.push_back(current_group);
  }

  int total = 0;
  for (auto group: groups) {
    map<char, int> counts;

    for (auto line: group) {
      for (auto chr: line) {
        counts[chr] += 1;
      }
    }

    total += counts.size();
  }

  return total;
}

int main() {
  int test_count = get_yes_counts("input/day6_test.txt");
  assert(test_count == 11);

  cout << "TEST PASSED" << endl;

  return 0;
}