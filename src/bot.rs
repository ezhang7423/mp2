pub trait Bot {
    fn get_move(&self) -> (usize, usize);
}
