pub mod frontend;
mod routes;

pub use frontend::run_frontend;

use actix_web::{App, HttpServer};

#[actix_web::main]
pub async fn run_backend() -> std::io::Result<()> {
    println!("Backend running at http://localhost:5000");
    HttpServer::new(|| App::new().service(routes::hello))
        .bind("127.0.0.1:5000")?
        .run()
        .await
}
