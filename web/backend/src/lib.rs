use actix_files as fs;
use actix_web::{App, HttpServer};

#[actix_web::main]
pub async fn run_server() -> std::io::Result<()> {
    println!("Running server");
    HttpServer::new(|| {
        App::new().service(fs::Files::new("/", "./web/frontend/dist").index_file("index.html"))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}

// use actix_web::{get, post, App, HttpResponse, HttpServer, Responder};

// #[get("/")]
// pub async fn hello() -> impl Responder {
//     HttpResponse::Ok().body("Hello world!")
// }

// #[actix_web::main]
// pub async fn run_server() -> std::io::Result<()> {
//     println!("Running at http://localhost:8080");
//     HttpServer::new(|| App::new().service(hello))
//         .bind("127.0.0.1:8080")?
//         .run()
//         .await
// }
