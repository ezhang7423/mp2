use crate::madam::mcts;
use crate::{bot::Bot, game::GameState};
use ndarray::{Array, Ix2};
use rand::Rng;

pub struct Madam {
    move_tree: mcts::Tree,
}
impl Madam {
    pub fn new(state: &GameState) -> Self {
        Madam {
            move_tree: mcts::Tree::new(state, None, None),
        }
    }
}

impl Bot for Madam {
    fn get_move(&self, state: &Array<usize, Ix2>, board_size: usize) -> (usize, usize) {
        let mut rng = rand::thread_rng();

        let n1: usize = rng.gen_range(0..board_size);
        let n2: usize = rng.gen_range(0..board_size);
        (n1, n2)
    }
}
