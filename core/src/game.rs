use serde::{Deserialize, Serialize};

use crate::bot::Bot;
use crate::madam::Madam;
use ndarray::{Array, Ix2};
use std::cmp::max;
use std::io;
use std::num::ParseIntError;

#[derive(Serialize, Deserialize)]
pub enum GameCondition {
    NotStarted,
    InProgress,
    Finished,
}

#[derive(Copy, Clone, Serialize, Deserialize)]
pub enum Player {
    Human = 1,
    Bot = 2,
}
pub type Pos = (usize, usize); // Position on board

#[derive(Serialize, Deserialize)]
pub struct GameState {
    pub current_player: Player,
    pub size: usize,
    waiting_player: Player,
    state: Array<usize, Ix2>,
}

impl GameState {
    pub fn new(size: usize, human_first: Option<bool>) -> Self {
        let human_first = human_first.unwrap_or(true);

        // assume that human starts
        let (mut current_player, mut waiting_player) = (Player::Human, Player::Bot);

        if !human_first {
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
    pub fn make_move(&mut self, player_move: Pos) -> bool {
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

    fn finished_helper(&self, i: usize, j: usize, horizontal: bool) -> bool {
        let first_color = self.state[[i, j]];
        let mut finished = true;
        for delta in 0..5 {
            // stop if there is any gap in the window
            let test_color = if horizontal {
                self.state[[i, j + delta]]
            } else {
                self.state[[i + delta, j]]
            };

            if test_color == 0 || test_color != first_color {
                finished = false;
                break;
            }
        }
        finished
    }

    fn finished_helper_diag(&self, left: bool) -> bool {
        let sz = self.size as i32;
        let iter_sz = sz - 4;

        for diag in (-iter_sz + 1..iter_sz).rev() {
            // println!("diag: {}", diag);
            for diag_idx in 0..(sz - diag.abs() - 4) {
                let i = max(diag, 0) + diag_idx;
                let j = (i - diag) as usize;
                let i = if left { i } else { sz - i - 1 } as usize;

                let mut finished = true;
                let first_color = self.state[[i, j]];

                for delta in 0..5 {
                    // println!("{}, {}", i + delta, j + delta);
                    let test_color = if left {
                        self.state[[i + delta, j + delta]]
                    } else {
                        self.state[[i - delta, j + delta]]
                    };
                    if test_color == 0 || test_color != first_color {
                        finished = false;
                        break;
                    }
                }
                if finished {
                    return true;
                }
            }
        }
        false
    }

    pub fn finished(&self) -> bool {
        // check with a sliding window from left to right, top to bottom
        for i in 0..self.size {
            for j in 0..self.size - 4 {
                if self.finished_helper(i, j, true) {
                    return true;
                }
            }
        }
        // top to bottom, left to right
        for j in 0..self.size {
            for i in 0..self.size - 4 {
                if self.finished_helper(i, j, false) {
                    return true;
                }
            }
        }

        // left diagonal from left to right
        if self.finished_helper_diag(true) {
            return true;
        }
        if self.finished_helper_diag(false) {
            return true;
        }

        false
    }
}
impl Clone for GameState {
    fn clone(&self) -> Self {
        GameState {
            current_player: self.current_player,
            size: self.size,
            waiting_player: self.waiting_player,
            state: self.state.clone(),
        }
    }
}

pub struct Game {
    game_state: GameState,
    condition: GameCondition,
    robot: Box<dyn Bot>,
}

impl Game {
    fn parse_move(input_text: &str) -> Result<Pos, ParseIntError> {
        let mut split = input_text.split(", ");
        Ok((
            split.next().unwrap_or("fail").parse::<usize>()?,
            split.next().unwrap_or("fail").parse::<usize>()?,
        ))
    }
    fn get_move(&self) -> Pos {
        let chosen_move: Pos;
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
                self.print();
                println!("Game finished. ");
                if matches!(self.game_state.current_player, Player::Human) {
                    println!("You won!")
                } else {
                    println!("You lost. Better luck next time.")
                }
                self.condition = GameCondition::Finished;
                break;
            }
        }
    }

    pub fn new(size: usize, human_first: Option<bool>) -> Self {
        let game_state = GameState::new(size, human_first);
        Self {
            condition: GameCondition::NotStarted,
            robot: Box::new(Madam::new(&game_state)),
            game_state: game_state,
        }
    }

    pub fn print(&self) {
        println!("\n\n\n{}\n\n\n", self.game_state.state);
    }
}
