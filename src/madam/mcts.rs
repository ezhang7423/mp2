use crate::game;

pub struct Node {
    value: f64,
    count: usize,
    children: Vec<Node>,
    state: game::GameState,
}

pub struct Tree {
    root: Node,
}

impl Tree {}
