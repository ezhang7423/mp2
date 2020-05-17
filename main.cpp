#include "gamestate.cpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

bool prod = true;
game parseArgs(char *arg1, char *ovalue, char *arg2 = (char *)"-d") {
  int size = 11;
  bool first;
  if (!strncmp(arg1, "-n", 2)) {
    size = atoi(ovalue);
  };
  first = (bool)(!strncmp(arg2, "-l", 2));
  return game(size, first);
};

game startup(int argc, char **argv) {
  if (std::getenv("PROD")) {
    prod = strncmp(std::getenv("PROD"), "FALSE", 5);
  }
  if (argc != 1) {
    if (argc == 2 && !strncmp(argv[1], "-l", 2)) {
      return game(11, true);
    } else if (argc == 3) {
      return parseArgs(argv[1], argv[2]);
    } else if (argc == 4) {
      return parseArgs(argv[1], argv[2], argv[3]);
    } else {
      cout << "USAGE: ./gobang -n <size> -l <bool> (first vs second)" << endl;
      exit(1);
    }
  } else {
    return game(11, false);
  }
}
int main(int argc, char **argv) {
  game g = startup(argc, argv);
  g.printBoard();
  cout << g.c << endl;
}