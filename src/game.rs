use crate::bot::Bot;
use crate::madam;
use ndarray::{Array, Ix2};
use std::io;
use std::num::ParseIntError;

pub enum GameCondition {
    NotStarted,
    InProgress,
    Finished,
}
#[derive(Copy, Clone)]
pub enum Player {
    Human = 1,
    Bot = 2,
}

pub struct GameState {
    pub current_player: Player,
    pub size: usize,
    waiting_player: Player,
    state: Array<usize, Ix2>,
}
impl GameState {
    pub fn new(size: usize, human_turn: Option<bool>) -> Self {
        let human_turn = human_turn.unwrap_or(true);

        // assume that human starts
        let (mut current_player, mut waiting_player) = (Player::Human, Player::Bot);

        if !human_turn {
            // black = Player::Human;
            // white = Player::Bot;
            current_player = Player::Bot;
            waiting_player = Player::Human
        }

        let state = Array::<usize, _>::zeros((size, size));
        Self {
            current_player,
            size,
            waiting_player,
            state,
        }
    }

    // returns whenther a move was succcessfully made or not
    pub fn make_move(&mut self, player_move: (usize, usize)) -> bool {
        if player_move.0 >= self.size || player_move.1 >= self.size {
            println!("Your move is out of bounds");
            return false;
        }
        if self.state[player_move] != 0 {
            println!("There has already been a stone placed here");
            return false;
        }
        self.state[player_move] = self.current_player as usize;

        if !self.finished() {
            // swap current and waiting
            let tmp = self.waiting_player;
            self.waiting_player = self.current_player;
            self.current_player = tmp;
        }
        true
    }
    pub fn finished(&self) -> bool {
        // check if Finished
        let mut finished = false;

        for i in 0..self.size {
            let first_color = self.state[[i, 0]];
            let mut successful = true;
            for j in 0..self.size {
                if self.state[[i, j]] == 0 || self.state[[i, j]] != first_color {
                    successful = false;
                    break;
                }
            }
            if successful {
                finished = true;
                break;
            }
        }

        finished
    }
}

pub struct Game {
    game_state: GameState,
    condition: GameCondition,
    robot: Box<dyn Bot>,
}

impl Game {
    fn parse_move(input_text: &str) -> Result<(usize, usize), ParseIntError> {
        let mut split = input_text.split(", ");
        Ok((
            split.next().unwrap_or("fail").parse::<usize>()?,
            split.next().unwrap_or("fail").parse::<usize>()?,
        ))
    }
    fn get_move(&self) -> (usize, usize) {
        let chosen_move: (usize, usize);
        if matches!(self.game_state.current_player, Player::Human) {
            self.print();
            loop {
                println!("What's your move? e.g. '2, 3'");
                let mut input_text = String::new();
                io::stdin()
                    .read_line(&mut input_text)
                    .expect("Failed to read from stdin");

                let trimmed = input_text.trim();
                match Game::parse_move(trimmed) {
                    Ok(i) => {
                        chosen_move = i;
                        break;
                    }
                    Err(..) => {
                        println!("Failed to parse your move: {}", trimmed);
                    }
                };
            }
        } else {
            // idk
            println!("Robot is thinking...");
            chosen_move = self
                .robot
                .get_move(&self.game_state.state, self.game_state.size);
            println!("Robot's move: {}, {}", chosen_move.0, chosen_move.1);
        }
        chosen_move
    }

    pub fn start(&mut self) {
        if !matches!(self.condition, GameCondition::NotStarted) {
            eprintln!("Game cannot be started in its current condition");
            return;
        }
        println!("Game has started!");
        self.condition = GameCondition::InProgress;

        loop {
            loop {
                let player_move = self.get_move();
                if self.game_state.make_move(player_move) {
                    break;
                }
            }
            if self.game_state.finished() {
                self.condition = GameCondition::Finished;
                self.print();
                break;
            }
        }
    }

    pub fn new(size: usize, human_turn: Option<bool>) -> Self {
        Self {
            condition: GameCondition::NotStarted,
            game_state: GameState::new(size, human_turn),
            robot: Box::new(madam::Madam {}),
        }
    }

    pub fn print(&self) {
        println!("\n\n\n{}\n\n\n", self.game_state.state);
    }
}
