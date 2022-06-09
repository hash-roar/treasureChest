use std::env;

use color_eyre::{Result};
use eyre::eyre;

use tracing::info;
use tracing_subscriber::{fmt,EnvFilter};


#[derive(Debug)]
pub struct  Config{
    pub src :String,
    pub des: String
}

impl Config {

    pub fn init()-> Result<Config> {
        fmt().with_env_filter(EnvFilter::from_default_env()).init();
        info!("load config...");
        let args:Vec<String> =env::args().collect();
        if args.len()!=3 {
            return Err(eyre!("not enough argument,you should set src and des"));
        }
        info!("config loaded:--> source:{},dest:{}",args[1],args[2]);
        Ok(Config{
            src: args[1].clone(),
            des: args[2].clone()
        })
    }
}

