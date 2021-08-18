use std::{
    cell::RefCell,
    rc::{Rc, Weak},
};

use crate::game::{GameState, Pos, StateTensor};


pub trait NeuralNet {
    fn get_pv(&mut self, state: &GameState) -> (StateTensor, f64);
}

//http://way-cooler.org/blog/2016/08/14/designing-a-bi-mutable-directional-tree-safely-in-rust.html
//https://joshondesign.com/2020/04/08/rust5_tree
type PNode = Option<Weak<RefCell<Node>>>;
type NodeChildren = Vec<Rc<Node>>;

const NUM_SIMULATIONS: i32 = 1000;
const EXPLORATION_COEF: f64 = 1.;
pub struct Node {
    value: f64,
    num_samples: usize,
    parent: PNode,
    children: NodeChildren,
    state: GameState,
    action: Option<Pos>,
}

impl Node {
    pub fn new(parent: PNode, state: GameState, action: Option<Pos>) -> Self {
        Node {
            value: 0.,
            num_samples: 0,
            parent,
            children: vec![],
            state,
            action,
        }
    }
    pub fn expand_children(&self) {}
}
pub struct Tree {
    root: Node,
    simulations: i32,
    exploration: f64,
}

impl Tree {
    pub fn new(state: &GameState, simulations: Option<i32>, exploration: Option<f64>) -> Self {
        Tree {
            root: Node::new(None, state.clone(), None),
            simulations: simulations.unwrap_or(NUM_SIMULATIONS),
            exploration: exploration.unwrap_or(EXPLORATION_COEF),
        }
    }

    pub fn find_move(&mut self, state: Option<&GameState>) -> Pos {
        if !state.is_none() {
            self.root = Node::new(None, state.unwrap().clone(), None);
        } 
        for _ in 0..self.simulations {
            let node = self.select(&self.root);
            node.expand_children();
            let selected_node = self.get_best(&node.children);
            let reward = self.rollout(selected_node);
            self.backup(selected_node, reward);
        }
        let mut best_choice = &self.root.children[0];
        for child in self.root.children.iter() {
            if child.num_samples > best_choice.num_samples {
                best_choice = &child;
            }
        }

        best_choice.action.unwrap()
    }
    fn select(&self, node: &Node) -> &Node {
        &self.root
    }

    fn rollout(&self, node: &Node) -> f64 {
        0.
    }

    fn backup(&self, node: &Node, reward: f64) {}

    fn get_best(&self, node: &NodeChildren) -> &Node {
        &self.root
    }
}
