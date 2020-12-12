#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>

using std::string;
using std::ifstream;
using std::list;
using std::cout;
using std::endl;
using std::next;

typedef struct Seat {
  int row;
  int column;
  int seat_id;
} Seat;

const int ROW_COUNT = 128;
const int COLUMN_COUNT = 8;

Seat *get_seat(string input) {
  int row = 0;
  int column = 0;
  int seat_id = 0;
  int row_lower = 0;
  int row_upper = ROW_COUNT - 1;
  int col_lower = 0;
  int col_upper = COLUMN_COUNT - 1;

  const string row_str = input.substr(0, 7);
  const string col_str = input.substr(7, 10);

  cout << "ROW STR: " << row_str << endl;
  cout << "COL STR: " << col_str << endl;

  for (string::const_iterator it = row_str.begin(); it != row_str.end(); ++it) {
    char chr = *it;
    cout << "ROW CHR: " << chr << endl;
    cout << "ROW UPP: " << row_upper << endl;
    cout << "ROW LOW: " << row_lower << endl;

    const int diff = row_upper - row_lower;
    int split = diff / 2;
    if (diff % 2 != 0) {
      split += (chr == 'B') ? -1 : 1;
    }

    if (chr == 'F') {
      row_upper -= split;
      cout << "ROW UPP AFTER: " << row_upper << endl;

      if (next(it) == row_str.end()) {
        row = row_upper;
      }
    } else if (chr == 'B') {
      row_lower += split;
      cout << "ROW LOW AFTER: " << row_lower << endl;

      if (next(it) == row_str.end()) {
        row = row_lower;
      }
    } else {
      continue;
    }
  }

  for (string::const_iterator it = col_str.begin(); it != col_str.end(); ++it) {
    const char chr = *it;

    cout << "COL CHR: " << chr << endl;
    cout << "UPP: " << col_upper << endl;
    cout << "LOW: " << col_lower << endl;

    const int diff = col_upper - col_lower;
    int split = diff / 2;
    if (diff % 2 != 0) {
      split += (chr == 'L') ? -1 : 1;
    }

    if (chr == 'L') {
      col_upper -= split;
      cout << "COL UPP: " << col_upper << endl;

      if (next(it) == col_str.end()) {
        column = col_upper;
        break;
      }
    } else if (chr == 'R') {
      col_lower += split;
      cout << "COL LOW: " << col_lower << endl;

      if (next(it) == col_str.end()) {
        column = col_lower;
        break;
      }
    } else {
      continue;
    }
  }

  seat_id = row * 8 + column;

  cout << "Seat: " << "row=" << row << "&col=" << column << "&seatid=" << seat_id << endl;

  return new Seat({ .row = row, .column = column, .seat_id = seat_id });
};

int main() {
  string test_input1 = "BFFFBBFRRR";
  Seat test_seat1 = Seat { .row = 70, .column = 7, .seat_id = 567 };
  Seat *test_result1 = get_seat(test_input1);
  assert(test_seat1.row == test_result1->row && test_seat1.column == test_result1->column && test_seat1.seat_id == test_result1->seat_id);
  
  string test_input2 = "FFFBBBFRRR";
  Seat test_seat2 = Seat { .row = 14, .column = 7, .seat_id = 119 };
  Seat *test_result2 = get_seat(test_input2);
  assert(test_seat2.row == test_result2->row && test_seat2.column == test_result2->column && test_seat2.seat_id == test_result2->seat_id);

  string test_input3 = "BBFFBBFRLL";
  Seat test_seat3 = Seat { .row = 102, .column = 4, .seat_id = 820 };
  Seat *test_result3 = get_seat(test_input3);
  assert(test_seat3.row == test_result3->row && test_seat3.column == test_result3->column && test_seat3.seat_id == test_result3->seat_id);

  ifstream file_stream;
  file_stream.open("input/day5.txt", std::ios::in);
  list<string> inputs;
  string line;
  int biggest_seat = 0;

  while (getline(file_stream, line)) {
    inputs.push_back(line);
  }

  for (auto input: inputs) {
    Seat *seat = get_seat(input);
    if (seat->seat_id > biggest_seat) {
      biggest_seat = seat->seat_id;
    }
  }

  cout << "biggest seat: " << biggest_seat << endl;

  return 0;
}