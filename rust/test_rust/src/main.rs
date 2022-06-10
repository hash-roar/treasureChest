mod proxy;
mod config;
mod connection;
mod timer;

use std::env;

use color_eyre::Result;
use proxy::ProxyServer;
use crate::config::Config;


#[tokio::main]
async fn  main() ->Result<()>{
    env::set_var("RUST_LOG", "debug");
    dotenv::dotenv().ok();
    
    let cfg = Config::init()?;

    let  server = ProxyServer::new(cfg);
    server.start().await?;
    Ok(())
}