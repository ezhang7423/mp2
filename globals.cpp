#pragma once
#include "library.cpp"
extern bool prod;

typedef std::pair<int, int> tupl;
typedef std::vector<tupl> tuplist;

void print(std::string s) {
  if (!prod) {
    std::cout << s << std::endl;
  }
}
