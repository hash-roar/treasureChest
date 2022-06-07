use actix_web::{get, web, HttpResponse, Responder};
use serde::{Deserialize, Serialize};
use sqlx::PgPool;

use crate::db;

pub async fn status() -> actix_web::HttpResponse {
    web::HttpResponse::Ok().body("hello")
}

// #[get("/u/{short_url}")]
pub async fn url(
    db_pool: web::Data<PgPool>,
    web::Path(short_url): web::Path<String>,
) -> impl Responder {
    let result = db::get_url(&db_pool, short_url).await;

    match result {
        Ok(url) => HttpResponse::Ok().body(url),
        Err(_) => HttpResponse::InternalServerError().into(),
    }
}

#[derive(Serialize, Deserialize)]
pub struct AddUrl {
    pub full_url: String,
}

pub async fn add_url(db_pool: web::Data<PgPool>, url_info: web::Json<AddUrl>) -> impl Responder {
    HttpResponse::Ok().body(url_info.full_url.clone())
}
