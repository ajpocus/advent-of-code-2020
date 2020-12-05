#include <vector>
#include <iterator>
#include <string>
#include <iostream>

#include "./common.hpp"

using namespace std;

string test_input_arr[] = {
  "..##.......",
  "#...#...#..",
  ".#....#..#.",
  "..#.#...#.#",
  ".#...##..#.",
  "..#.##.....",
  ".#.#.#....#",
  ".#........#",
  "#.##...#...",
  "#...##....#",
  ".#..#...#.#"
};

typedef struct Position {
  int x = 0;
  int y = 0;
} Position;

class Grid {
  // first dimension is "row", second dimension is "column"
  // so tree_map[0][1] is the second column of the first row
  vector< vector<char> > tree_map;
  Position position;
  size_t row_length;

  public:

  Grid(vector<string>);
  int step_x();
  int step_x(int);
  int step_y();
  int step_y(int);
  int count_trees(int, int);
};

Grid::Grid(vector<string> lines) {
  for (int x = 0; x < lines[0].size(); ++x) {
    vector<char> chrs;

    for (int y = 0; y < lines.size(); ++y) {
      chrs.push_back(lines[y][x]);
    }

    tree_map.push_back(chrs);
  }

  row_length = tree_map[0].size();
}

int Grid::step_x() {
  return step_x(1);
}

int Grid::step_x(int step) {
  return (position.x + step) % row_length;
}

int Grid::step_y() {
  return step_y(1);
}

int Grid::step_y(int step) {
  return position.y + step;
}

int Grid::count_trees(int xrun, int yrun) {
  int y_limit = tree_map.size();
  int treecount = 0;

  while (position.y < y_limit) {
    int target_x = step_x(xrun);
    int target_y = step_y(yrun);
    
    cout << "target x: " << target_x << "\n";
    cout << "target y: " << target_y << "\n";

    int x = position.x;
    int y = position.y;

    while (x != target_x) {
      cout << "x, y: " << x << ", " << y << "\n";

      char chr = tree_map[y][x];
      if (chr == '#') {
          ++treecount;
      }

      x = step_x();
    }

    while (y < target_y) {
      cout << "x, y: " << x << ", " << y << "\n";
      
      char chr = tree_map[y][x];
      if (chr == '#') {
          ++treecount;
      }

      y = step_y();
    }
  }

  return treecount;
}

int main() {
  vector<string> test_input;
  int len = sizeof(test_input_arr) / sizeof(string);
  for (int i = 0; i < len; ++i) {
    test_input.push_back(test_input_arr[i]);
  }

  Grid *test_grid = new Grid(test_input);
  int test_tree_count = test_grid->count_trees(3, 1);
  cout << test_tree_count << "\n";
  assert(test_tree_count == 7);

  vector<string> in = get_file("input/day3.txt");
  Grid *grid = new Grid(in);

  int xrun = 3;
  int yrun = 1;
  int tree_count = grid->count_trees(xrun, yrun);

  cout << tree_count << "\n";

  delete(grid);
  
  return 0;
}