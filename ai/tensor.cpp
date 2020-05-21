
#include <cassert>
#include <iostream>
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

  static void add(tensor &res, int tn, tensor &l, tensor &r) {
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
      int ol = res.shape[2] * res.shape[1];
      int z = ops % ol;
      int f = ops - ol * z;
      int y = f % res.shape[2];
      int x = f / res.shape[2];
      res(x, y, z) = l(x, y, z) + r(x, y, z);
    }
  }
  void (*addd)(tensor &, int, tensor &, tensor &){add};
  tensor &operator+(tensor &b) {
    multithread(addd, *this, *this, b);
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

int main() {
  tensor b(2, 3, 5);
  tensor a(2, 3, 5);
  cout << a + b << endl;
}