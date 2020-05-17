#include "../gamestate.cpp"
#include <utility>
typedef std::pair<int, int> tupl;

tupl think(game &g) { return std::make_pair(5, 6); }