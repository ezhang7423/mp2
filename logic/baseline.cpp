#include "../ai/funcs.cpp"
#include "../gamestate.cpp"
#include <corecrt_math.h>
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
  node(node *p, float prior) {
    this->p = prior;
    this->parent = p;
  }
  node *parent;
  unordered_map<int, node *> children; // inefficient for looping?
  int numvisits;
  int q = 0;
  int u = 0;
  int p = 0;
  void expand(vpairf priors) {
    for (int i = 0; i < priors.second.size(); i++) {
      node *tmp;
      if (!children[priors.first[i]]) {
        tmp = new node(this, priors.second[i]);
        children[priors.first[i]] = tmp;
      }
    }
  };
  pair<int, node *> select(float puct) {
    pair<int, node *> best;
    int bestval = -INFINITY;
    for (auto i : children) {
      if (i.second->get_val(puct) > bestval) {
        best = i;
      }
    }
    return best;
  };
  void update(float q) {
    this->numvisits++;
    this->q += 1 * (q - this->q) / this->numvisits; // avg value
  };
  void update_recursive(float q) {
    if (this->parent) {
      this->parent->update_recursive(-q);
    }
    this->update(q);
  };
  float get_val(float puct) {
    this->u = (puct * this->p * sqrt(this->parent->numvisits) /
               (1 + this->numvisits));
    return (this->q + this->u);
  };
};
typedef pair<int, node *> avpair;
class ts {
public:
  void playout(game &g) {
    node *n = root;
    while (true) {
      if (n->children.size() == 0) {
        break;
      }
      avpair av = n->select(this->pucts);
      g.update(i2tupl(av.first, g.size));
    }
    // vpairf av = policy(state);
    int leaf;
    if (g.isFull() || g.checkWon(g.state3)) {
      if (g.isFull()) {
        leaf = 0;
      }
      if ((g.current == 2) && (g.checkWon(g.state2))) {
        leaf = 1;
      } else if ((g.current == 3) && (g.checkWon(g.state3))) {
        leaf = 1;
      } else {
        leaf = -1;
      }
    } else {
      // expand
    }
    n->update_recursive(-leaf);
  };
  void update(int last) {
    bool invicinity = false;
    for (auto i : root->children) {
      if (last == i.first) {
        invicinity = true;
        break;
      }
    }
    if (invicinity) {
      root = root->children[last];
      root->parent = nullptr;
    } else {
      root = new node(nullptr, 1.0);
    }
  };

  ts(){};
  ts(int playouts, int pucts) : playouts(playouts), pucts(pucts) {
    root = new node(nullptr, 1.0);
  }
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
    return arr;
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
  int pucts;
};

// the ai
class Madam {
public:
  Madam(int playouts = 400, int pucts = 5) { brain = ts(playouts, pucts); }
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