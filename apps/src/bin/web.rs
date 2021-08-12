use server;
use std::thread;

const RUN_BACKEND: bool = true;
const RUN_FRONTEND: bool = false;

fn run_backend() {
    match server::run_backend() {
        Ok(res) => res,
        Err(e) => eprintln!("Error in starting server: {}", e),
    }
}

fn run_frontend() {
    match server::run_frontend() {
        Ok(res) => res,
        Err(e) => eprintln!("Error in starting frontend: {}", e),
    }
}

fn main() {
    if RUN_BACKEND && RUN_FRONTEND {
        let backend_handle = thread::spawn(run_backend);
        let frontend_handle = thread::spawn(run_frontend);
        backend_handle.join().unwrap();
        frontend_handle.join().unwrap();
    } else if RUN_BACKEND {
        run_backend();
    } else if RUN_FRONTEND {
        run_frontend();
    }
}
