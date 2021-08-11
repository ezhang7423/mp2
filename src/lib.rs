pub mod bot;
pub mod game;
pub mod madam {
    mod head;
    mod mcts;
    pub use head::Madam;
}
