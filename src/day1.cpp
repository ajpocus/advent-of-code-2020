#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef std::vector<int>::iterator iter;

int get_pair_product(vector<int> input) {
  for (int i = 0; i < input.size(); ++i) {
    for (int j = i + 1; j < input.size(); ++j) {
      int a = input[i];
      int b = input[j];

      if (a + b == 2020) {
        return a * b;
      }
    }
  }

  return -1;
}

int get_tri_product(vector<int> input) {
  for (int i = 0; i < input.size(); ++i) {
    for (int j = i + 1; j < input.size(); ++j) {
      for (int k = j + 1; k < input.size(); ++k) {
        int a = input[i],
          b = input[j],
          c = input[k];
        
        if (a + b + c == 2020) {
          return a * b * c;
        }
      }
    }
  }

  return -1;
}

int main() {
  // test pair product
  static const int test_arr[] = {1721, 979, 366, 299, 675, 1456};
  vector<int> test_input;
  int len = sizeof(test_arr) / sizeof(int);
  for (int i = 0; i < len; ++i) {
    test_input.push_back(test_arr[i]);
  }

  int test_product = get_pair_product(test_input);
  int expected_product = 514579;
  assert(test_product == expected_product);

  ifstream input_file;
  input_file.open("input/day1.txt", ios::in);

  if (!input_file.is_open()) {
    return -1;
  }

  // get input
  string line;
  vector<int> input;
  while (getline(input_file, line)) {
    input.push_back(stoi(line));
  }

  // output first test result
  int product = get_pair_product(input);
  cout << product << "\n";

  int expected_tri = 241861950;
  int test_tri_product = get_tri_product(test_input);
  assert(test_tri_product == expected_tri);

  int tri_product = get_tri_product(input);
  cout << tri_product << "\n";

  return 0;
}