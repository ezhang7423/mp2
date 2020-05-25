#pragma once
#include "matrix.cpp"

class game {
public:
  game(){};
  game(game &right) {
    this->size = right.size;
    this->moves = right.moves;
    this->current = right.current;
    this->lastmove = right.lastmove;
    this->prod = right.prod;
    this->state1 = right.state1;
    this->state2 = right.state2;
    this->state3 = right.state3;
  }
  game(int size, bool first) {
    this->size = size;
    this->moves = size * size;
    this->state1 = matrix(size);
    this->state2 = matrix(size);
    this->state3 = matrix(size);
    if (first) {
      current = 1;
    } else {
      current = 2;
    }
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
  void update(tupl move) {
    if (current == 1) {
      this->state1(move) = 1;
    } else if (current == 2) {
      this->state2(move) = 1;
    }
    this->state3(move) = current;
    this->history.push_back(move);
    current = 3 - current;
    lastmove = move;
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
  int current;
  tupl lastmove;
  bool prod;
  matrix state1;
  matrix state2;
  matrix state3;
  tuplist history;
};