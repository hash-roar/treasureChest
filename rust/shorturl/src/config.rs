use config::ConfigError;
use serde::Deserialize;

#[derive(Deserialize)]

pub struct ServerConfig {
    pub host: String,
    pub port: i32,
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
#[derive(Deserialize)]
pub struct Config {
    pub server: ServerConfig,
    pub db: deadpool_postgres::Config,
    // pub cache: CacheConfig,
}

impl Config {
    pub fn from_env() -> Result<Self, ConfigError> {
        let mut cfg = config::Config::new();
        cfg.merge(config::Environment::new())?;
        cfg.try_into()
        //Ok(())
    }
}
