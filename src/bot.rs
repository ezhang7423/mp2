use ndarray::{Array, Ix2};
pub trait Bot {
    fn get_move(&self, state: &Array<usize, Ix2>, board_size: usize) -> (usize, usize);
}
