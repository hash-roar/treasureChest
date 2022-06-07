use color_eyre::Result;
use eyre::WrapErr;
use serde::Deserialize;
use sqlx::postgres::PgPool;
use tracing::{info, instrument};
use tracing_subscriber::EnvFilter;

#[derive(Deserialize, Debug)]

pub struct ServerConfig {
    pub host: String,
    pub port: i32,
    pub database_url: String,
}

// temporarily unused
// #[derive(Deserialize)]
// pub struct DbConfig {
//     pub host: String,
//     pub port: i32,
//     pub dbname: String,
//     pub user: String,
//     pub password: String,
// }

// #[derive(Deserialize)]
// pub struct CacheConfig {
//     pub host: String,
//     pub port: i32,
//     pub secret: String,
// }
#[derive(Deserialize, Debug)]
pub struct Config {
    pub server: ServerConfig,
    // pub cache: CacheConfig,
}

impl Config {
    #[instrument]
    pub fn from_env() -> Result<Config> {
        let mut cfg = config::Config::new();
        cfg.merge(config::Environment::new())?;

        tracing_subscriber::fmt()
            .with_env_filter(EnvFilter::from_default_env())
            .init();
        info!("load config");
        cfg.try_into().context("load config from environment")
        //Ok(())
    }

    pub async fn db_pool(&self) -> Result<PgPool> {
        info!("creating database connection");

        PgPool::connect(&self.server.database_url)
            .await
            .context("connect to database error")
    }
}
