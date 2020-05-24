#include "library.cpp"
#include <string>
#include <utility>

using namespace std;
mat reshape(list rp, int width, int height) {
  if (width == -1) {
    width = rp.size() / height;
  } else if (height == -1) {
    height = rp.size() / width;
  }
  mat res(height, width);
  int j = 0;
  for (auto i : rp) {
    // cout << (to_string(i)) << endl;
    int r = j / width;
    int c = j % width;
    res(r, c) = i;
    j++;
  }
  return res;
};

template <typename T> std::vector<T> arange(T start, T stop, T step = 1) {
  std::vector<T> values;
  for (T value = start; value < stop; value += step)
    values.push_back(value);
  return values;
}

mat broadcast(list a, list b) {
  // mat *res = new mat(b.size(), a.size());
  mat res(b.size(), a.size());
  for (unsigned i = 0; i < b.size(); i++) {
    for (unsigned j = 0; j < a.size(); j++) {
      res(i, j) = b[i] + a[j];
    }
  }
  return res;
};
list repeat(list rp, int num) {
  list res(rp.size() * num);
  int j = 0;
  for (auto &&i : res) {
    i = rp[j / num];
    j++;
  }
  return res;
}
list tile(list rp, int num) {
  // cout << num << endl;
  list res(rp.size() * num);
  int j = 0;
  for (auto &&i : res) {
    i = rp[j % rp.size()];
    j++;
  }
  return res;
}
mat3 cols(mat3 &shape, int h, int w, int s, int p) {
  int channels = shape.depth;
  int outputsize = (shape.row_size - h + 2 * p) / s + 1;
  list i0 = repeat(arange(0, h), w);
  i0 = tile(i0, channels);
  list i1 = repeat(arange(0, outputsize), outputsize);
  // for (auto &&i : i1) {
  //   i *= s;
  // }
  list j0 = tile(arange(0, w), h * channels);
  list j1 = tile(arange(0, outputsize), outputsize);
  // for (auto &&i : j1) {
  //   i *= s;
  // }
  mat *i = new mat(1, 1);
  *i = broadcast(i1, i0);
  mat *j = new mat(1, 1);
  *j = broadcast(j1, j0);
  mat3 res = mat3(2, i->row_size, i->col_size);
  res.arr[0] = i;
  res.arr[1] = j;
  return res;
}
// mat3 reformat(mat3 &rp, mat3 &indices) {
//   // kij for indices
//   mat3 *res = new mat3(rp.depth, rp.row_size, rp.col_size);
//   for ()
// }

int main() {
  list test = arange(0, 5);
  list test2 = arange(0, 5);
  // mat *f = new mat(1, 1);
  // *f = broadcast(test2, test);
  // cout << *f << endl;
  // delete f;
  mat *f = new mat(10, 10);
  mat3 testb(1, 5, 5);
  testb.arr[0] = f;

  mat3 boi = cols(testb, 3, 3, 1, 2);
  boi.print();
  // cout << "yay!" << endl;
  // boi.print();
  //   for (auto i : test) {
  //     cout << i << endl;
  //   }
}
