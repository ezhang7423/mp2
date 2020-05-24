
#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
typedef std::pair<int, int> tupl;
typedef std::vector<int> list;
typedef std::vector<float> listf;
typedef std::pair<list, list> vpair;
typedef std::pair<listf, listf> vpairf;

const int THREADS_NUMBER = 12;
tupl getWork(int amt, int workers, int tn) {
  return std::make_pair(amt * tn / workers, amt * (tn + 1) / workers);
}

template <class T> const T &max(const T &a, const T &b) {
  return (a < b) ? b : a;
}
class ran {
public:
  ran() {
    gen = std::mt19937(rd());
    random = std::uniform_real_distribution<>(0, 1);
  }
  float getRandom() { return random(gen); }
  int getRandomMove(vpairf av, bool noisy = false) {
    float val = random(gen);
    float cval = 0;
    int i = 0;
    while (cval < val) {
      cval += av.second[i];
      if (cval >= val) {
        return av.first[i];
      }
      i++;
    }
    return -1;
  }

private:
  std::random_device rd;
  std::uniform_real_distribution<> random;
  std::mt19937 gen;
};
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
  mat(int row_size, int col_size, float fill = 0, bool rand = false)
      : col_size(col_size), row_size(row_size) {
    if (rand) {
    }
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
  void relu() { multithread(reluu, *this, *this, *this); }

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
  static void reluu(mat &result, mat &m1, mat &m2, int tn) {
    tupl work = getWork(m1.row_size * m1.col_size, THREADS_NUMBER, tn);
    for (int i = work.first; i < work.second; ++i) {
      int r = i / m2.col_size;
      int c = i % m2.col_size;
      result(r, c) = max(result(r, c), (float)0);
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
  m1.multithread(m1.mult, *result, m1, m2);
  return *result;
}

mat &operator+(mat &m1, mat &m2) {
  assert(m1.col_size == m2.col_size);
  assert(m1.row_size == m2.row_size);
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
  mat3(){};
  int col_size;
  int row_size;
  int depth;
  void relu() {
    for (auto &&i : arr) {
      i->relu();
    }
  }
  mat3(int depth, int row_size, int col_size, float fill = 0,
       bool rand = false) {
    arr.resize(depth);
    for (auto &&i : arr) {
      i = new mat(row_size, col_size, fill, rand);
    }
  }
  void print() {
    for (auto &&i : arr) {
      std::cout << *i << std::endl;
    }
  }
  ~mat3() {
    for (auto &&i : arr) {
      i->clear();
    }
  }
  std::vector<mat *> arr;
};

// #include <chrono>
// #include <ctime>
// using namespace std;
// bool prod = true;
// int main() {
//   int MID = 10000;
//   mat test(MID, 3);
//   for (int i = 0; i < MID; i++) {
//     for (int j = 0; j < 3; j++) {
//       test(i, j) = i + j;
//     }
//   }
//   // mat test3 = test;
//   mat test2(3, MID);
//   for (int i = 0; i < MID; i++) {
//     for (int j = 0; j < 3; j++) {
//       // test3(i, j) = i + j;
//     }
//   }
//   // cout << test << endl;
//   // cout << test2 << endl;
//   auto a = std::chrono::steady_clock::now();
//   // mat test4 = test2 * test;
//   // cout << test4 << endl;
//   auto b = std::chrono::steady_clock::now();
//   cout << THREADS_NUMBER << endl;
//   cout << std::chrono::duration_cast<std::chrono::duration<double>>(b - a)
//               .count()
//        << endl;
// }
