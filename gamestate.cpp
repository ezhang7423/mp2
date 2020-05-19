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
    this->state = matrix(size);
    if (first) {
      this->c = 1; // first
    } else {
      this->c = 2; // second
    }
    this->h = 3 - this->c; // makes h the other guy
  }
  std::string won() { 
    
  }
  void update(tupl move, int sig) {
    this->state(move) = sig;
    this->history.push_back(move);
  }
  void printBoard() {
    if (!prod) {
      std::cout << this->state << std::endl;
    }
  }
  ~game() { state.clear(); }
  bool prod;
  matrix state;
  int c; // color of computer. 1 = Dark, 2 = White
  int h; // color of human
  tuplist history;
};