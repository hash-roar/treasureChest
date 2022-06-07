mod config;
mod db;
mod error;
mod handlers;
mod models;

use std::io;

use crate::handlers::*;
use actix_web::{middleware::Logger, web, App, HttpServer};
use dotenv::dotenv;
use sqlx::postgres::PgPool;
use tracing::info;

#[actix_rt::main]
async fn main() -> io::Result<()> {
    dotenv().ok();
    let config = crate::config::Config::from_env().expect("error happen when load config");

    let pool = config.db_pool().await.expect("connect to database  error");

    info!(
        "start server at: http://{}:{}/",
        config.server.host, config.server.port
    );
    HttpServer::new(move || {
        App::new()
            .wrap(Logger::default())
            .data(pool.clone())
            .route("/", web::get().to(status))
            .route("/u/{short_url}", web::get().to(url))
            .route("/url", web::post().to(add_url))
    })
    .bind(format!("{}:{}", config.server.host, config.server.port))?
    .run()
    .await
}
