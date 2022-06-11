use std::{
    collections::HashMap,
    sync::{
        atomic::{self, AtomicU64},
        Arc, Mutex,
    },
};

use color_eyre::Result;
use tokio::net::TcpListener;
use tracing::{info, warn};

use crate::{
    config::Config,
    connection::{ProxyConnection, ProxyState},
};

type ProxyConnsPtr = Arc<Mutex<HashMap<u64, Arc<ProxyConnection>>>>;

#[derive(Debug)]
pub struct ProxyServer {
    pub config: Config,
    pub total_counter: atomic::AtomicU64,
    pub connection_counter: Arc<atomic::AtomicU64>,
    pub connections: ProxyConnsPtr,
}

impl ProxyServer {
    pub fn new(config: Config) -> Self {
        ProxyServer {
            config: config,
            total_counter: AtomicU64::new(0),
            connection_counter: Arc::new(AtomicU64::new(0)),
            connections: Arc::new(Mutex::new(HashMap::new())),
        }
    }

    pub async fn collect_info(conn_ptr: ProxyConnsPtr) -> Result<()> {
        let (connecting, connected) = (0, 0);

        Ok(())
    }

    pub async fn start(&self) -> Result<()> {
        let listener = TcpListener::bind(&self.config.src).await?;
        info!(
            "ProxyServer Start at: {}  ===> {}",
            &self.config.src, &self.config.des
        );

        loop {
            let conn = Arc::new(ProxyConnection::new());
            let des = self.config.des.clone();
            let (tcp_stream, addr) = listener.accept().await?;

            let conn_counter = self.connection_counter.clone();
            let conns = self.connections.clone();

            let index: u64;
            conn_counter.fetch_add(1, atomic::Ordering::Relaxed);
            {
                *conn.state.lock().unwrap() = ProxyState::FromConnSet;
                // to unlock
            }
            {
                let mut conns = conns.lock().unwrap();
                index = self.total_counter.fetch_add(1, atomic::Ordering::AcqRel);
                conns.insert(index, conn.clone());
            }
            tokio::spawn(async move {
                let result = conn.process(tcp_stream, addr, des).await;

                // self.total_counter.fetch_sub(1, atomic::Ordering::Relaxed);
                // TODO()

                //after the connection
                conn_counter.fetch_sub(1, atomic::Ordering::AcqRel);
                {
                    conns.lock().unwrap().remove(&index);
                }
                match result {
                    Ok(_) => {}
                    Err(err) => {
                        warn!("{}", err.to_string());
                    }
                }
            });
        }
    }
}
