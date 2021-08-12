use actix_files as fs;
use actix_web::{App, HttpServer};

#[actix_web::main]
pub async fn run_frontend() -> std::io::Result<()> {
    println!("Frontend running at http://localhost:8080");
    HttpServer::new(|| {
        App::new().service(fs::Files::new("/", "./web/frontend/dist").index_file("index.html"))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
