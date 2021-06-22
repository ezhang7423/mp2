mod bot;
mod game;
mod madam;

use clap::{AppSettings, Clap};
use std::process::exit;

/// Play Gomoku against the madam
#[derive(Clap)]
#[clap(version = "1.0", author = "Edwin Z. <ete@ucsb.edu>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Opts {
    /// Size of the board. 5 <= n <= 18
    #[clap(short, long, default_value = "11")]
    n: usize,
    /// Whether you go first or second
    #[clap(short, long)]
    first: Option<bool>,
}

fn parse_args() -> Opts {
    let opts: Opts = Opts::parse();

    if opts.n < 5 || opts.n > 18 {
        eprintln!("n is invalid");
        exit(1);
    }

    opts
}

fn main() {
    let opts = parse_args();
    println!("Size of the board: {}", opts.n);
    println!("Your moves are denoted by '1'. The robot's moves are denoted by '2'\n");
    let mut game = game::Game::new(opts.n, opts.first);
    game.start();
}
