#include <iostream>
#include <fstream>
#include <string>
#include <list>

using std::string;
using std::ifstream;
using std::list;
using std::cout;
using std::endl;

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

  for (auto chr: input) {
    cout << "CHR: " << chr << endl;

    if (chr == 'F') {
      row_upper -= (row_upper - row_lower) / 2;
      cout << "ROW UPP: " << row_upper << endl;

      if (row_lower == row_upper) {
        row = row_upper;
      }
    } else if (chr == 'B') {
      row_lower += (row_upper - row_lower) / 2;
      cout << "ROW LOW: " << row_lower << endl;

      if (row_lower == row_upper) {
        row = row_lower;
      }
    } else if (chr == 'L') {
      col_lower += (col_upper - col_lower) / 2;
      cout << "COL LOW: " << col_lower << endl;

      if (col_lower == col_upper) {
        column = col_lower;
        break;
      }
    } else if (chr == 'R') {
      col_upper -= (col_upper - col_lower) / 2;
      cout << "COL UPP: " << col_upper << endl;

      if (col_lower == col_upper) {
        column = col_lower;
        break;
      }
    } else {
      continue;
    }
  }

  seat_id = row * 8 + column;

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