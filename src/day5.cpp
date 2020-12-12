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

int get_index(string input, int init_upper_bound, char lower_char, char upper_char) {
  int lower_bound = 0;
  int upper_bound = init_upper_bound;
  int index = -1;

  for (string::const_iterator it = input.begin(); it != input.end(); ++it) {
    char chr = *it;
    cout << "ROW CHR: " << chr << endl;
    cout << "ROW UPP: " << upper_bound << endl;
    cout << "ROW LOW: " << lower_bound << endl;

    const int diff = upper_bound - lower_bound;
    int split = diff / 2;
    if (diff % 2 != 0) {
      split += (chr == 'F') ? -1 : 1;
    }

    if (chr == 'F') {
      upper_bound -= split;
      cout << "ROW UPP AFTER: " << upper_bound << endl;

      if (next(it) == input.end()) {
        index = upper_bound - 1;
      }
    } else if (chr == 'B') {
      lower_bound += split;
      cout << "ROW LOW AFTER: " << lower_bound << endl;

      if (next(it) == input.end()) {
        index = lower_bound + 1;
      }
    } else {
      continue;
    }
  }

  return index;
};

Seat *get_seat(string input) {
  int row_upper = ROW_COUNT - 1;
  int col_upper = COLUMN_COUNT - 1;

  const int row_str_len = 7;
  const int col_str_len = 3;
  const string row_str = input.substr(0, row_str_len);
  const string col_str = input.substr(row_str_len, row_str_len + col_str_len);

  cout << "ROW STR: " << row_str << endl;
  cout << "COL STR: " << col_str << endl;

  int row = get_index(row_str, row_upper, 'F', 'B');
  int column = get_index(col_str, col_upper, 'L', 'R');
  int seat_id = row * 8 + column;

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