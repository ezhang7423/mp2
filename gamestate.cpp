#pragma once
#include "matrix.cpp"
#include <string>
#include <utility>
#include <vector>
typedef std::pair<int, int> tupl;
typedef std::vector<tupl> tuplist;

class game {
public:
  game(){};
  game(int size, bool first) {
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
  std::string won() {}
  void update(tupl move, int sig) {
    if (sig == 1) {
      this->state1(move) = 1;
    } else if (sig == 2) {
      this->state2(move) = 1;
    }
    this->state3(move) = sig;
    this->history.push_back(move);
  }
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
  bool prod;
  matrix state1;
  matrix state2;
  matrix state3;
  int c; // color of computer. 1 = Dark, 2 = White
  int h; // color of human
  tuplist history;
};