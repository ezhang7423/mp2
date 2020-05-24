#include "library.cpp"
#include <string>

using namespace std;
mat reshape(list rp, int width, int height) {
  if (width == -1) {
    width = rp.size() / height;
  } else if (height == -1) {
    height = rp.size() / width;
  }
  mat *res = new mat(height, width);
  int j = 0;
  for (auto i : rp) {
    // cout << (to_string(i)) << endl;
    int r = j / width;
    int c = j % width;
    (*res)(r, c) = i;
    j++;
  }
  return *res;
};

template <typename T> std::vector<T> arange(T start, T stop, T step = 1) {
  std::vector<T> values;
  for (T value = start; value < stop; value += step)
    values.push_back(value);
  return values;
}

mat broadcast(list a, list b) {
  mat *res = new mat(b.size(), a.size());
  for (int i = 0; i < b.size(); i++) {
    for (int j = 0; j < a.size(); j++) {
      (*res)(i, j) = b[i] + a[j];
    }
  }
  return *res;
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
  list res(rp.size() * num);
  int j = 0;
  for (auto &&i : res) {
    i = rp[j % rp.size()];
    j++;
  }
  return res;
}

int main() {
  list test = arange(-5, 0);
  list test2 = arange(0, 3);
  mat f = broadcast(test2, test);
  cout << f << endl;
  //   for (auto i : test) {
  //     cout << i << endl;
  //   }
}