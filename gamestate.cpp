#include "matrix.cpp"
#include <utility>
#include <vector>

typedef std::pair<int, int> tuple;
typedef std::vector<tuple> tuplist;

class game {
public:
  game(){};
  game(int size, bool first) {
    this->state = matrix(size);
    if (first) {
      this->c = 1; // first
    } else {
      this->c = 2; // second
    }
    this->h = 3 - this->c; // makes h the other guy
  }
  ~game() { state.clear(); }
  void printBoard() { std::cout << this->state << std::endl; }
  matrix state;
  int c;
  int h;
  tuplist history;
};