#include "matrix.cpp"

using namespace std;

int main() {
  matrix m(5);
  m(1, 1) = 5;
  cout << m << endl;
}