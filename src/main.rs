use clap::{AppSettings, Clap};
use std::process::exit;

mod game;

/// Play Gomoku against the madam
#[derive(Clap)]
#[clap(version = "1.0", author = "Edwin Z. <ete@ucsb.edu>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Opts {
    /// Size of the board. 5 <= n <= 18
    #[clap(short, long, default_value = "11")]
    n: usize,
    // /// Whether you go first or second
    // #[clap(short, long)]
    // first: Option<bool>,
    /// A level of verbosity, and can be used multiple times
    #[clap(short, long, parse(from_occurrences))]
    verbose: i32,
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
    let  game = game::Game::new(opts.n, None);
    game.start();    
}
