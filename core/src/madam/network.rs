use ndarray::Array;

use crate::game::{GameState, StateTensor};

pub struct PVnet {}

impl PVnet {
    pub fn new() -> Self {
        PVnet {}
    }
    pub fn load(path: &str) -> Self {
        PVnet {}
    }

    pub fn save() {}
    pub fn get_pv(&mut self, state: &GameState) -> (StateTensor, f64) {
        (Array::<usize, _>::zeros((0, 0)), 0.)
    }
}
