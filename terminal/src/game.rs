use core::{
    game::{Bot, GameCondition, GameState, Player, Pos},
    madam::MadamTrain,
};
use std::{io, num::ParseIntError};

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
            chosen_move = self.robot.get_move(&self.game_state);
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
        self.game_state.print();
    }
}
