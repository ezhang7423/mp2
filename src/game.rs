use ndarray::{Array, Ix2};



enum GameCondition {
    NotStarted,
    InProgress,
    Finished,
}
#[derive(Copy, Clone)]
enum Player {
    Human = 0,
    Bot = 1,
}
pub struct Game {
    pub size: usize,
    condition: GameCondition,
    // black: Player,
    // white: Player,
    current_player: Player,
    waiting_player: Player,
    state: Array<usize, Ix2>,
}

impl Game {
    fn finished(&self) -> bool {
        // check if Finished
        let finished = false;

        finished
    }
    fn get_move(&self) -> (usize, usize) {
        if matches!(self.current_player, Player::Human) {
            println!("What's your move?")
        } else {
            // idk
        }
        (0, 0)
    }

    pub fn start(&mut self) {
        if matches!(self.condition, GameCondition::NotStarted) {
            eprintln!("Game cannot be started in its current condition");
            return;
        }
        self.condition = GameCondition::InProgress;

        loop {
            self.print();
            let player_move = self.get_move();
            self.state[player_move] = self.current_player as usize;

            if self.finished() {
                self.condition = GameCondition::Finished;
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

        // assume that Bot starts
        let (mut black, mut white, mut current_player, mut waiting_player) =
            (Player::Bot, Player::Human, Player::Bot, Player::Human);
        if human_first {
            // black = Player::Human;
            // white = Player::Bot;
            current_player = Player::Human;
            waiting_player = Player::Bot
        }

        let state = Array::<usize, _>::zeros((size, size));

        Self {
            size,
            condition: GameCondition::NotStarted,
            // black,
            // white,
            current_player,
            waiting_player,
            state: state,
        }
    }

    pub fn print(&self) {
        println!("{}", self.state);
    }
}
