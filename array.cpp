#include "globals.cpp"
#include <string>
#include <thread>
const int THREADS_NUMBER = 1;
class mat {
public:
  int col_size;
  int row_size;
  int **arr;
  mat(int row_size, int col_size, int fill = 0)
      : col_size(col_size), row_size(row_size) {
    this->arr = new int *[row_size];
    for (int i = 0; i < row_size; i++) {
      arr[i] = new int[col_size];
    }
    for (int i = 0; i < row_size; i++) {
      for (int j = 0; j < col_size; j++) {
        arr[i][j] = fill;
      }
    }
  }
  friend std::ostream &operator<<(std::ostream &os, mat &m);
  int &operator()(tupl a) { return arr[a.first][a.second]; }
  int &operator()(int i, int j) { return arr[i][j]; }
  friend mat &operator*(mat &m1, mat &m2);
  friend void multiplication_thr(mat &m1, mat &m2, mat &result, const int tn);
  //   mat &operator*(mat &m2) {
  //     std::thread threads[THREADS_NUMBER];
  //     mat *result = new mat(col_size, m2.row_size);
  //     for (int i = 0; i < THREADS_NUMBER; ++i) {
  //       threads[i] = std::thread(multiplication_thr, this, std::ref(*this),
  //                                std::ref(m2), std::ref(*result),
  //                                std::ref(i));
  //     }
  //     for (int i = 0; i < THREADS_NUMBER; ++i) {
  //       threads[i].join();
  //     }
  //     return *result;
  //   }
  void clear() {
    for (int i = 0; i < this->row_size; i++) {
      delete[] arr[i];
    }
    delete[] arr;
  }
};
using namespace std;
void print(std::string a) { std::cout << a << std::endl; }
void multiplication_thr(mat &m1, mat &m2, mat &result, int tn) {
  tn--;
  int start, end;
  if (tn == 0) {
    start = 0;
    end = (m1.col_size / THREADS_NUMBER) + m1.col_size % THREADS_NUMBER;
  } else {
    start = (m1.row_size / THREADS_NUMBER) * tn + m1.row_size % THREADS_NUMBER;
    end = (m1.row_size / THREADS_NUMBER) * (tn + 1) +
          m1.row_size % THREADS_NUMBER;
  }
  print("START FROM: " + std::to_string(tn) + "\n" + std::to_string(start) +
        "\n");
  print("END FROM: " + std::to_string(tn) + "\n" + std::to_string(end) + "\n");

  /*
  m1 r, c = 3, 5
  m2 r, c = 5, 2
  m3 r, c = 3, 2
  [ 0 , 1,]
  [ 2,  3,]
  [ 4,  5]
  */
  /*
   */
  for (int i = start; i <= end; ++i) {
    int r = i / m2.col_size;
    int c = i % m1.row_size;
    for (int j = 0; j < m2.col_size; ++j) {
      for (int k = 0; k < m1.row_size; ++k) {
        cout << c << endl;
        // result(r, c) = 5;
        // result.arr[r][c] += m1.arr[i][k] * m2.arr[k][j];
      }
    }
  }
}
mat &operator*(mat &m1, mat &m2) {
  std::thread threads[THREADS_NUMBER];
  mat *result = new mat(m1.row_size, m2.col_size);
  for (int i = 0; i < THREADS_NUMBER; ++i) {
    threads[i] = std::thread(multiplication_thr, std::ref(m1), std::ref(m2),
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

using namespace std;
int main() {
  mat test(3, 5);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      test(i, j) = i + j;
    }
  }
  mat test2(5, 2);
  test2(1, 0) = 10;
  //   cout << test << endl;
  //   cout << test2 << endl;
  cout << test * test2 << endl;
}