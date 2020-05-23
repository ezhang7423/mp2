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
  unordered_map<int, node *> children;
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
  void playout(game &g){}; // todo
  void update(int move){}; // tood

  ts(){};
  ts(int playouts, int explore) : playouts(playouts), explore(explore) {}
  vpairf getPairs() {
    listf acts;
    listf visits;
    for (auto i : root->children) {
      acts.push_back(i.first);
      visits.push_back(i.second->numvisits);
    }
    return std::make_pair(acts, visits);
  }
  listf mcweight(listf arr, float temp) {
    float weight = 1.0 / temp;
    for (auto &&i : arr) {
      i += 1e-10;
      i = log(i);
      i *= weight;
    }
  }

  vpairf getProbs(game &g, float temp) {
    game tmp;
    for (int i = 0; i < playouts; i++) {
      tmp = g;
      playout(tmp);
    };
    vpairf av = getPairs();
    av.second = mcweight(av.second, temp); // transform visits to probabilities
    return av;
  }

private:
  node *root;
  int playouts;
  int explore;
};

class ran {
public:
  ran() {
    gen = mt19937(rd());
    random = std::uniform_real_distribution<>(0, 1);
  }
  float getRandom() { return random(gen); }
  int getRandomMove(vpairf av, bool noisy = false) {
    float val = random(gen);
    float cval = 0;
    int i = 0;
    while (cval < val) {
      cval += av.second[i];
      if (cval >= val) {
        return av.first[i];
      }
      i++;
    }
    return -1;
  }

private:
  random_device rd;
  std::uniform_real_distribution<> random;
  mt19937 gen;
};
// the ai
class Madam {
public:
  Madam(int playouts = 400, int explore = 5) { brain = ts(playouts, explore); }
  void reset() { brain.update(-1); }
  tupl think(game &g, float temp = 1e-3) {
    vpairf ap = brain.getProbs(g, temp); // actions, probabilities
    if (!g.isFull()) {
      int move = rng.getRandomMove(ap, training);
      brain.update(-1);
      return tupl(move / g.size, move % g.size);
    }
    return tupl(-1, -1);
  }
  std::pair<tupl, matrix>
  think_self(game &g, float temp = 1e-3) { // temp=temperature, stochasity
    vpairf ap = brain.getProbs(g, temp);   // actions, probabilities
    if (!g.isFull()) {
      int move = rng.getRandomMove(ap, training);
      brain.update(move);
      matrix m(g.size);
      for (auto i : ap.first) {
        m((int)i / g.size, (int)i % g.size) = ap.second[i];
      }
      return std::make_pair(tupl(move / g.size, move % g.size), m);
    }
    return std::make_pair(tupl(-1, -1), matrix(g.size));
  }

  // return std::make_pair(5, 6); }  for playing against self
private:
  ts brain; // implementation of monte carlo tree search
  ran rng;
  bool training;
};