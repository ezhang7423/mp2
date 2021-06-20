use clap::{AppSettings, Clap};
use std::process::exit;

/// Play Gomoku against the robot
#[derive(Clap)]
#[clap(version = "1.0", author = "Edwin Z. <ete@ucsb.edu>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Opts {
    /// Size of the board. 5 <= n <= 18
    #[clap(short, long, default_value = "5")]
    n: u8,
    // /// Whether you go first or second
    // #[clap(short, long)]
    // first: Option<bool>,
    /// A level of verbosity, and can be used multiple times
    #[clap(short, long, parse(from_occurrences))]
    verbose: i32,
}

fn main() {
    let opts: Opts = Opts::parse();

    if opts.n < 5 || opts.n > 18 {
        eprintln!("n is invalid");
        exit(1);
    }

    // // Vary the output based on how many times the user used the "verbose" flag
    // // (i.e. 'myprog -v -v -v' or 'myprog -vvv' vs 'myprog -v'
    match opts.verbose {
        0 => println!("No verbose info"),
        1 => println!("Some verbose info"),
        2 => println!("Tons of verbose info"),
        3 | _ => println!("Maximum supported verbosity is 2"),
    }
    
}
