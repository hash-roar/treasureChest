use std::sync::{ atomic::{self, AtomicU64}};

use color_eyre::Result;
use tokio::net::TcpListener;
use tracing::{instrument, info};

use crate::{config::Config, connection::{ProxyConnection, ProxyState}};


#[derive(Debug)]
pub struct  ProxyServer{
    pub config:Config,
    pub total_counter: atomic::AtomicU64,
    pub connection_counter: atomic::AtomicU64 
}

impl ProxyServer {

    pub fn new(config:Config) -> Self{
        ProxyServer { config: config,
        total_counter:AtomicU64::new(0),
        connection_counter:AtomicU64::new(0) }
    }     

    
    async fn start(&mut self) -> Result<()>{
        let listener = TcpListener::bind(&self.config.src).await?;

        loop {
            let mut conn = ProxyConnection::new();
            let des = self.config.des.clone();
            let (tcp_stream,addr) = listener.accept().await?;
            conn.state = ProxyState::FromConnSet;
            
            tokio::spawn(async move {
            let result =   conn.process(tcp_stream, addr, des).await;
            match result {
                Ok(_)=>{},
                Err(err) => {
                    info!("{}",err.to_string());
                }
            }
           });
        }

        Ok(())   
    }
}