use actix_web::{get, post, web, App, HttpResponse, HttpServer, Responder};

#[get("/")]
pub async fn hello() -> impl Responder {
 HttpResponse::Ok().body("Hello world!")
}

#[post("/echo")]
pub async fn echo(req_body: String) -> impl Responder {
    HttpResponse::Ok().body(req_body)
}


#[actix_web::main]
pub async fn run_server() -> std::io::Result<()> {
    println!("Running at http://localhost:8080");
    HttpServer::new(|| {
        App::new()
            .service(hello)
            .service(echo)





            
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
