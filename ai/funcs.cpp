#pragma once
#include "../library.cpp"

using namespace std;

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

// int TtoInt(tupl a){

// }

// tupl ItoT(tupl b){

// }