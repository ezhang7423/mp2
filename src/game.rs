use crate::bot::Bot;
use crate::madam;
use ndarray::{Array, Ix2};
use std::io;
use std::num::ParseIntError;

enum GameCondition {
    NotStarted,
    InProgress,
    Finished,
}
#[derive(Copy, Clone)]
enum Player {
    Human = 1,
    Bot = 2,
}
pub struct Game {
    // size: usize,
    condition: GameCondition,
    current_player: Player,
    waiting_player: Player,
    state: Array<usize, Ix2>,
    robot: Box<dyn Bot>,
}

impl Game {
    fn finished(&self) -> bool {
        // check if Finished
        let finished = false;

        finished
    }

    fn parse_move(input_text: &str) -> Result<(usize, usize), ParseIntError> {
        let mut split = input_text.split(", ");
        Ok((
            split.next().unwrap_or("fail").parse::<usize>()?,
            split.next().unwrap_or("fail").parse::<usize>()?,
        ))
    }
    fn get_move(&self) -> (usize, usize) {
        let chosen_move: (usize, usize);
        if matches!(self.current_player, Player::Human) {
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
            chosen_move = self.robot.get_move();
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
                if self.state[player_move] == 0 {
                    self.state[player_move] = self.current_player as usize;
                    break;
                } else {
                    println!("There has already been a stone placed here")
                }
            }

            if self.finished() {
                self.condition = GameCondition::Finished;
                self.print();
                break;
            } else {
                // swap current and waiting
                let tmp = self.waiting_player;
                self.waiting_player = self.current_player;
                self.current_player = tmp;
            }
        }
    }

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
            // size,
            condition: GameCondition::NotStarted,
            current_player,
            waiting_player,
            state: state,
            robot: Box::new(madam::Madam {}),
        }
    }

    pub fn print(&self) {
        println!("\n\n\n{}\n\n\n", self.state);
    }
}
