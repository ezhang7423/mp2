use crate::bot::Bot;
pub struct Madam {}

impl Bot for Madam {
    fn get_move(&self) -> (usize, usize) {
        return (0, 0);
    }
}
