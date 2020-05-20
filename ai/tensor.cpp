#include <iostream>
using namespace std;
// copy
// add
// multiply

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
  os << "-------------end-------------";
  return os;
}