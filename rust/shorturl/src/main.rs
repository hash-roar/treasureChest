mod config;
mod db;
mod error;
mod handlers;
mod models;

use std::io;

use crate::handlers::*;
use actix_web::{web, App, HttpServer};
use dotenv::dotenv;
use tokio_postgres::NoTls;

#[actix_rt::main]
async fn main() -> io::Result<()> {
    dotenv().ok();
    let config = crate::config::Config::from_env().unwrap();
    let pool = config.db.create_pool(NoTls).unwrap();

    HttpServer::new(move || {
        App::new()
            .data(pool.clone())
            .route("/", web::get().to(status))
    })
    .bind(format!("{}:{}", config.server.host, config.server.port))?
    .run()
    .await
}
