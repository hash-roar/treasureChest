use std::io;

use crate::models::*;
use deadpool_postgres::Client;
use tokio_pg_mapper::FromTokioPostgresRow;

pub async fn get_url(client: &Client, short_code: String) -> Result<Url, io::Error> {
    let statement = client
        .prepare("select * from urls WHERE short_code = $1")
        .await
        .unwrap();

    client
        .query(&statement, &[&short_code])
        .await
        .expect("query databse error")
        .iter()
        .map(|row| Url::from_row_ref(row).unwrap())
        .collect::<Vec<Url>>()
        .pop()
        .ok_or(io::Error::new(io::ErrorKind::Other, "error get url"))
}
