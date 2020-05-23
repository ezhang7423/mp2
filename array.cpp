#include "globals.cpp"
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
const int THREADS_NUMBER = 1;
tupl getWork(int amt, int workers, int tn) {
  return std::make_pair(amt * tn / workers, amt * (tn + 1) / workers);
}
class mat {
public:
  int col_size;
  int row_size;
  float **arr;
  mat &operator=(const mat &other) {
    clear();
    this->arr = new float *[other.row_size];
    for (int i = 0; i < row_size; i++) {
      arr[i] = new float[other.col_size];
    }
    for (int i = 0; i < other.row_size; i++) {
      for (int j = 0; j < other.col_size; j++) {
        arr[i][j] = other.arr[i][j];
      }
    }
    return *this;
  }
  mat(){};
  mat(int row_size, int col_size, float fill = 0)
      : col_size(col_size), row_size(row_size) {
    this->arr = new float *[row_size];
    for (int i = 0; i < row_size; i++) {
      arr[i] = new float[col_size];
    }
    for (int i = 0; i < row_size; i++) {
      for (int j = 0; j < col_size; j++) {
        arr[i][j] = fill;
      }
    }
  }
  friend std::ostream &operator<<(std::ostream &os, mat &m);
  float &operator()(tupl a) { return arr[a.first][a.second]; }
  float &operator()(int i, int j) { return arr[i][j]; }
  friend mat &operator*(mat &m1, mat &m2);
  friend mat &operator+(mat &m1, mat &m2);
  ~mat() { clear(); }
  void clear() {
    for (int i = 0; i < this->row_size; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }

private:
  static void multithread(void (*exec)(mat &res, mat &l, mat &r, int tn),
                          mat &res, mat &l, mat &r) {
    std::thread threads[THREADS_NUMBER];
    for (int i = 0; i < THREADS_NUMBER; ++i) {

      threads[i] =
          std::thread(exec, std::ref(res), std::ref(l), std::ref(r), i);
    }

    for (int i = 0; i < THREADS_NUMBER; ++i) {
      // std::cout << "Join thread " << i << std::endl;
      threads[i].join();
    }
  }
  static void add(mat &result, mat &m1, mat &m2, int tn) {
    tupl work = getWork(m1.row_size * m1.col_size, THREADS_NUMBER, tn);
    for (int i = work.first; i < work.second; ++i) {
      int r = i / m2.col_size;
      int c = i % m2.col_size;
      result(r, c) = m1(r, c) + m2(r, c);
    }
  }
  static void mult(mat &result, mat &m1, mat &m2, int tn) {

    tupl work = getWork(m1.row_size * m2.col_size, THREADS_NUMBER, tn);

    for (int i = work.first; i < work.second; ++i) {
      int r = i / m2.col_size;
      int c = i % m2.col_size;
      for (int j = 0; j < m2.row_size; ++j) {
        result(r, c) += m1(r, j) * m2(j, c);
      }
    }
  }
};
mat &operator*(mat &m1, mat &m2) {
  mat *result = new mat(m1.row_size, m2.col_size);
  std::cout << "START TEST" << std::endl;
  m1.multithread(m1.mult, *result, m1, m2);
  return *result;
}

mat &operator+(mat &m1, mat &m2) {
  assert(m1.col_size == m2.col_size);
  assert(m1.row_size == m2.row_size);
  // std::cout << "hi" << std::endl;
  mat *result = new mat(m1.row_size, m1.col_size);
  m1.multithread(m1.add, *result, m1, m2);
  return *result;
}

std::ostream &operator<<(std::ostream &os, mat &m) {
  for (int i = 0; i < m.row_size; i++) {
    for (int j = 0; j < m.col_size; j++) {
      os << m(i, j) << " ";
    }
    os << "\n";
  }
  return os;
}

class mat3 {
public:
  int col_size;
  int row_size;
  int depth;
  mat3(int depth, int row_size, int col_size, float fill = 0) {
    arr.resize(depth);
    for (auto &&i : arr) {
      i = new mat(row_size, col_size, fill);
    }
  }

  std::vector<mat *> arr;

private:
};
