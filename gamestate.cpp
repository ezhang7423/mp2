#pragma once
#include "matrix.cpp"

class game {
public:
  game(){};
  game(int size, bool first) {
    this->size = size;
    this->moves = size * size;
    this->state1 = matrix(size);
    this->state2 = matrix(size);
    this->state3 = matrix(size);
    if (first) {
      this->c = 1; // first
    } else {
      this->c = 2; // second
    }
    this->h = 3 - this->c; // makes h the other guy
  }
  bool checkWon(matrix &m) {
    int current = 0;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (m(i, j) != 1) {
          current = 0;
        } else {
          current++;
        }
        if (current == 5) {
          return true;
        }
      }
    }
    current = 0;
    for (int j = 0; j < size; j++) {
      for (int i = 0; i < size; i++) {
        if (m(i, j) != 1) {
          current = 0;
        } else {
          current++;
        }
        if (current == 5) {
          return true;
        }
      }
    }
    current = 0;
    for (int y = 0; y <= 2 * (size - 1); y++) {
      for (int i = std::max(0, y - size + 1); i <= std::min(size - 1, y); i++) {
        int j = y - i;
        if (m(i, j) != 1) {
          current = 0;
        } else {
          current++;
        }
        if (current == 5) {
          return true;
        }
      }
    }
    current = 0;
    for (int y = 2 * (size - 1); y >= 0; y--) {
      for (int i = std::max(0, y - size + 1); i <= std::min(size - 1, y); i++) {
        int j = size - 1 - (y - i);
        if (m(i, j) != 1) {
          current = 0;
        } else {
          current++;
        }
        if (current == 5) {
          return true;
        }
      }
    }
  };
  std::string won() {
    if (checkWon(state1)) {
      return "1";
    } else if (checkWon(state2)) {
      return "2";
    } else {
      return "";
    }
  } // returns string of who has won
  void update(tupl move, int sig) {
    if (sig == 1) {
      this->state1(move) = 1;
    } else if (sig == 2) {
      this->state2(move) = 1;
    }
    this->state3(move) = sig;
    this->history.push_back(move);
    moves--;
  }
  bool isFull() { return moves == 0; }
  void printBoard() {
    if (!prod) {
      std::cout << this->state3 << std::endl;
    }
  }
  ~game() {
    state1.clear();
    state2.clear();
    state3.clear();
  }
  int size;
  int moves;
  bool prod;
  matrix state1;
  matrix state2;
  matrix state3;
  int c; // color of computer. 1 = Dark, 2 = White
  int h; // color of human
  tuplist history;
};