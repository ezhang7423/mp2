
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
using namespace std;
// copy
// add
// multiply
const int THREADS_NUMBER = 8;

class tensor {
public:
  int shape[3];
  int ***arr;
  tensor() {}
  tensor(int s1, int s2, int s3) { init(s1, s2, s3); }
  void init(int s1, int s2, int s3, int fill = 0) {
    shape[0] = s1;
    shape[1] = s2;
    shape[2] = s3;

    this->arr = new int **[s1];
    for (int i = 0; i < s1; i++) {
      arr[i] = new int *[s2];
      for (int j = 0; j < s2; j++) {
        arr[i][j] = new int[s3];
        for (int k = 0; k < s3; k++) {
          arr[i][j][k] = fill;
        }
      }
    }
  }
  friend std::ostream &operator<<(std::ostream &os, tensor &m);

  static void multithread(void (*exec)(tensor &res, int tn, tensor &l,
                                       tensor &r),
                          tensor &res, tensor &l, tensor &r) {
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

  static void print(string s, int tn) { cout << tn << ":  " << s << endl; }
  static void add(tensor &res, int tn, tensor &l, tensor &r) {
    for (int i = 0; i < 3; i++) {
      assert(l.shape[i] == r.shape[i]);
    }
    int total = res.shape[0] * res.shape[1] * res.shape[2];
    int ops = total / THREADS_NUMBER;
    int rest = total % THREADS_NUMBER;
    int s, e;
    if (tn == 0) {
      s = 0;
      e = (ops * (tn + 1) + rest);
    } else {
      s = ops * tn + rest;
      e = (ops * (tn + 1)) + rest;
    }
    for (int i = s; i < e; i++) {
      //   print("i: " + to_string(i), tn);
      int ol = res.shape[2] * res.shape[1];
      int z = i / ol;
      int f = i - ol * z;
      int y = f / res.shape[2];
      int x = f % res.shape[2];
      res(z, y, x) = l(z, y, x) + r(z, y, x);
    }
  }
  void (*addd)(tensor &, int, tensor &, tensor &){add};
  tensor &operator+(tensor &b) {
    multithread(addd, *this, *this, b);
    return *this;
  }

  static void multiply(tensor &res, int tn, tensor &l, tensor &r) {

    assert(l.shape[2] == r.shape[0]);
    int total = res.shape[0] * res.shape[1] * res.shape[2];
    int ops = total / THREADS_NUMBER;
    int rest = total % THREADS_NUMBER;
    int s, e;
    if (tn == 0) {
      s = 0;
      e = (ops * (tn + 1) + rest);
    } else {
      s = ops * tn + rest;
      e = (ops * (tn + 1)) + rest;
    }
    for (int i = s; i < e; i++) {
      //   print("i: " + to_string(i), tn);
      int ol = res.shape[2] * res.shape[1];
      int z = i / ol;
      int f = i - ol * z;
      int y = f / res.shape[2];
      int x = f % res.shape[2];
      // if (z >= 2 || x >= 5 || y >= 3) {
      //   cout << "BADD!!!!" << endl;
      //   print("x: " + to_string(x), tn);
      //   print("y: " + to_string(y), tn);
      //   print("z: " + to_string(z), tn);
      // }

      res(z, y, x) = l(z, y, x) + r(z, y, x);
    }
  }
  void (*mult)(tensor &, int, tensor &, tensor &){multiply};
  tensor &operator*(tensor &b) {
    multithread(mult, *this, *this, b);
    return *this;
  }

  int &operator()(int i, int j, int k) { return arr[i][j][k]; }
  void clear() {
    for (int i = 0; i < shape[0]; i++) {
      for (int j = 0; j < shape[1]; j++) {
        delete[] arr[i][j];
      }
      delete[] arr[i];
    }
    delete[] arr;
  }
};

std::ostream &operator<<(std::ostream &os, tensor &m) {

  for (int i = 0; i < m.shape[0]; i++) {
    os << "--------new layer----------\n";
    for (int j = 0; j < m.shape[1]; j++) {
      for (int k = 0; k < m.shape[2]; k++) {

        os << m.arr[i][j][k] << " ";
      }
      os << "\n";
    }
  }
  os << "-----------end-------------";
  return os;
}

// int main() {
//   tensor b(2000, 300, 500);
//   for (int i = 0; i < 2000; i++) {
//     b(0, 0, i) = 10;
//   }
//   tensor a(2000, 300, 500);
//   for (int i = 0; i < 2000; i++) {
//     a(0, 0, i) = 10;
//   }
//   a + b;
//   //   cout << a + b << endl;
// }