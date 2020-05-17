#include "gamestate.cpp"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

game parseArgs(char *arg1, char *ovalue, char *arg2 = (char *)"-d") {
  int size = 11;
  bool first;
  if (!strncmp(arg1, "-n", 2)) {
    size = atoi(ovalue);
  };
  first = (bool)(!strncmp(arg2, "-l", 2));
  return game(size, first);
};

int main(int argc, char **argv) {
  if (argc != 1) {
    if (argc == 3) {
      game game = parseArgs(argv[1], argv[2]);
    } else if (argc == 4) {
      game game = parseArgs(argv[1], argv[2], argv[3]);
    } else {
      cout << "USAGE: ./gobang -n <size> -l <bool> (first vs second)" << endl;
      return 1;
    }
  } else {
    game game(11, false);
    game.printBoard();
  }
}