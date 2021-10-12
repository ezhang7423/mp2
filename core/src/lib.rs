pub mod bot;
pub mod game;
mod utils;

pub mod madam {
    mod head;
    mod mcts;
    pub use head::Madam;
}
