
use actix_web::{ResponseError,HttpResponse}; 
use derive_more::Display;

#[derive(Debug,Display)]
pub enum  ServiceError {
    #[display(fmt="resource not found")]
    NotFound,
    #[display(fmt="server error")]
    InternalServerError,
}

impl ResponseError for ServiceError {
    fn error_response(&self) -> HttpResponse {
        match self{
            ServiceError::NotFound => {
                HttpResponse::Forbidden().finish()
            }
            _ =>{
                HttpResponse::BadRequest().finish()
            }
        }
    }
}