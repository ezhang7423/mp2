#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <system_error>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

typedef vector<int> list;
typedef vector<float> listf;
typedef pair<list, list> vpair;
typedef pair<listf, listf> vpairf;

listf softmax(listf x) {
  float max = *max_element(begin(x), end(x));
  listf res;
  for (auto &&i : x) {
    res.push_back(exp(i - max));
  }
  float sum = 0;
  for (auto &&i : res) {
    sum += i;
  }
  for (auto &&i : res) {
    i /= sum;
  }
  return res;
}
