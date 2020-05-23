#include "globals.cpp"
#include <string>
#include <thread>
const int THREADS_NUMBER = 4;
class mat {
public:
  int col_size;
  int row_size;
  float **arr;
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
  friend void multiplication_thr(mat &m1, mat &m2, mat &result, const float tn);
  ~mat() { clear(); }
  void clear() {
    for (int i = 0; i < this->row_size; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }

private:
  static void multithread(void (*exec)(mat &res, int tn, mat &l, mat &r),
                          mat &res, mat &l, mat &r) {
    std::thread threads[THREADS_NUMBER];
    for (int i = 0; i < THREADS_NUMBER; ++i) {
      threads[i] =
          std::thread(exec, std::ref(res), i, std::ref(l), std::ref(r));
    }
    for (int i = 0; i < THREADS_NUMBER; ++i) {
      // std::cout << "Join thread " << i << std::endl;
      threads[i].join();
    }
  }
  static void multiplication_thr(mat &m1, mat &m2, mat &result, int tn) {
    tn--;
    int start, end;
    start = (m1.row_size * m2.col_size * tn) / THREADS_NUMBER;
    end = (m1.row_size * m2.col_size * (tn + 1)) / THREADS_NUMBER;

    for (int i = start; i < end; ++i) {
      int r = i / m2.col_size;
      int c = i % m2.col_size;
      for (int j = 0; j < m2.row_size; ++j) {
        result(r, c) += m1(r, j) * m2(j, c);
      }
    }
  }
};
mat &operator*(mat &m1, mat &m2) {
  std::thread threads[THREADS_NUMBER];
  mat *result = new mat(m1.row_size, m2.col_size);
  for (int i = 0; i < THREADS_NUMBER; ++i) {
    threads[i] = std::thread(m1.multiplication_thr, std::ref(m1), std::ref(m2),
                             std::ref(*result), std::ref(i));
  }
  for (int i = 0; i < THREADS_NUMBER; ++i) {
    threads[i].join();
  }
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

#include <chrono>
#include <ctime>
using namespace std;
int main() {
  int MID = 5000;
  mat test(MID, 3);
  for (int i = 0; i < MID; i++) {
    for (int j = 0; j < 3; j++) {
      test(i, j) = i + j;
    }
  }
  mat test2(3, MID);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < MID; j++) {
      test2(i, j) = ((i % 2) * 2 - 1) * i * j;
    }
  }
  auto a = std::chrono::steady_clock::now();
  test *test2;
  auto b = std::chrono::steady_clock::now();
  cout << THREADS_NUMBER << endl;
  cout << std::chrono::duration_cast<std::chrono::duration<double>>(b - a)
              .count()
       << endl;
}