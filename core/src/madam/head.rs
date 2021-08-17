use onnxruntime::environment::Environment;
use onnxruntime::session::Session;
use onnxruntime::{GraphOptimizationLevel, LoggingLevel, OrtError};

use crate::game::{Bot, GameState};
use crate::madam::mcts;

pub struct MadamTrain {
    move_tree: mcts::Tree,
    network: String,
}

fn construct_model(onnx_path: &str) -> Result<Session, OrtError> {
    let environment = Environment::builder()
        .with_name("test")
        .with_log_level(LoggingLevel::Verbose)
        .build()?;
    let session = environment
        .new_session_builder()?
        .with_optimization_level(GraphOptimizationLevel::Basic)?
        .with_number_threads(1)?
        .with_model_from_file(onnx_path)?;

    return Ok(session);
}
impl MadamTrain {
    pub fn new(onnx_path: &str, state: &GameState) -> Self {
        MadamTrain {
            move_tree: mcts::Tree::new(state, None, None),
            network: String::from(onnx_path),
        }
    }
}

impl Bot for MadamTrain {
    fn get_move(&mut self, state: &GameState) -> (usize, usize) {
        return self.move_tree.find_move(Some(state));
    }
}
