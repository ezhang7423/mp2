#include "../gamestate.cpp"
#include <utility>
typedef std::pair<int, int> tupl;

tupl think(game &g) {
  // do monte carlo tree search here
  // theory:
  // https://jeffbradberry.com/posts/2015/09/intro-to-monte-carlo-tree-search/
  // implementation with alpha zero:
  // https://github.com/junxiaosong/AlphaZero_Gomoku/blob/master/mcts_alphaZero.py

  // i will get you the probability and value at each state, so don't worry
  // about that. you can just use the dummy functions below for now
  return std::make_pair(5, 6);
}

int value(game &g) {
  return 1; // higher value means higher chance comuter will win with this state
}

matrix getProbs(game &g) {
  return matrix(g.state1.size); // a probability for each possible move
}