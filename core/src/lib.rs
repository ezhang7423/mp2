pub mod bot;
pub mod game;
pub mod train;
pub mod madam {
    mod head;
    mod mcts;
    pub use head::Madam;
}
