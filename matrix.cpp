#pragma once
#include "globals.cpp"

class matrix {
public:
  int size;
  int **arr;
  matrix() {}
  matrix(int size) { init(size); }
  void init(int size, int fill = 0) {
    this->size = size;
    this->arr = new int *[size];
    for (int i = 0; i < size; i++) {
      arr[i] = new int[size];
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        arr[i][j] = fill;
      }
    }
  }
  friend std::ostream &operator<<(std::ostream &os, matrix &m);
  int &operator()(tupl a) { return arr[a.first][a.second]; }
  int &operator()(int i, int j) { return arr[i][j]; }
  void clear() {
    for (int i = 0; i < this->size; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }
};

std::ostream &operator<<(std::ostream &os, matrix &m) {
  // os << "h";
  os << "\x1B[32m   ";
  for (int i = 1; i <= m.size; i++) {
    os << (char)(i + 64) << " ";
  }
  os << "\033[0m\n";
  for (int i = 0; i < m.size; i++) {
    if (i < 9) {
      os << "\x1B[32m" << (i + 1) << "\033[0m  ";
    } else {
      os << "\x1B[32m" << (i + 1) << "\033[0m ";
    }
    for (int j = 0; j < m.size; j++) {
      os << m.arr[i][j] << " ";
    }
    os << "\n";
  }
  return os;
}
