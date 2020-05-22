#include "../ai/funcs.cpp"
#include "../gamestate.cpp"
#include <unordered_map>
#include <utility>
// alpha zero resources:
// https://medium.com/applied-data-science/how-to-build-your-own-alphazero-ai-using-python-and-keras-7f664945c188
// http://tim.hibal.org/blog/alpha-zero-how-and-why-it-works/
// https://medium.com/applied-data-science/alphago-zero-explained-in-one-diagram-365f5abf67e0

// do monte carlo tree search here
// theory:
// https://jeffbradberry.com/posts/2015/09/intro-to-monte-carlo-tree-search/
// implementation with alpha zero:
// https://github.com/junxiaosong/AlphaZero_Gomoku/blob/master/mcts_alphaZero.py

// i will get you the probability and value at each state, so don't worry
// about that. you can just use the dummy functions below for now. this means
// no rollouts, and no computation of upper confidence

// monte carlo tree search

struct node {
  node *parent;
  unordered_map<string, node *> children;
  int numvisits;
  int q = 0;
  int u = 0;
  int p = 0;
  void expand();
  void select();
  void update();
  void update_recursive();
  void get_val();
};
class ts {
public:
  void playout(game &g){};
  listf getProbs(game &g, float temp) {
    game tmp;
    for (int i = 0; i < playouts; i++) {
      tmp = g;
      playout(tmp);
    };
  }

private:
  node *root;
  int playouts;
};

// the ai
class Madam {
public:
  tupl think(game &g, float temp = 1e-3) {
    listf acts = brain.getProbs(g, temp);
  }
  // tupl think_self(game &g, float temp=1e-3) { temp=temperature, stochasity
  // return std::make_pair(5, 6); }  for playing against self
private:
  ts brain;
};