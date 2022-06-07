use color_eyre::Result;

use sqlx::{query, PgPool, query_as};

pub async fn get_url(pool: &PgPool, short_code: String) -> Result<String> {
    let query_str = "select full_url from urls WHERE short_code = $1";
    let result: (String,) = query_as(query_str).bind(short_code).fetch_one(pool).await?;
    Ok(result.0)
}
