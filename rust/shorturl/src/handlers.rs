use actix_web::{web, Responder,HttpResponse};
use deadpool_postgres::Pool;

use crate::db;

pub async fn status() -> actix_web::HttpResponse {
    web::HttpResponse::Ok().body("hello")
}

pub async fn url(db_pool: web::Data<Pool>) -> impl Responder {
    let client = db_pool.get().await.expect("error happens to the database");

    let result = db::get_url(&client).await;

    match result {
        Ok(url) => HttpResponse::Ok().json(url),
        Err(_)=> HttpResponse::InternalServerError().into() 
    }

}
