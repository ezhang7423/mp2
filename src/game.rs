use ndarray::{Array, Ix2};

pub struct Game {
    pub size: usize,
    pub state: Array<usize, Ix2>,
}

impl Game {
    pub fn new(size: usize) -> Self {
        let state = Array::<usize, _>::zeros((size, size));
        Self { size, state: state }
    }
}
