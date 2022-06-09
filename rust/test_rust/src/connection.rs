use std::net::{ SocketAddr};

use color_eyre::Result;
use tokio::{net::TcpStream, io::{BufReader, BufWriter}, select};
use tracing::instrument;

#[derive(Debug)]
pub enum ProxyState {
    Init,
    FromConnSet,
    ToConnSetting,
    Established,
    ShutDowning,
    Error
}

#[derive(Debug)]
pub struct  ProxyConnection{
    pub state:ProxyState,
}

impl ProxyConnection {
    pub fn new()-> ProxyConnection{
        ProxyConnection{
            state: ProxyState::Init
        }
    }

    #[instrument]
     pub async fn process(&mut self,mut tcp:TcpStream,addr: SocketAddr,des :String) -> Result<()>{
        let (reader, mut writer ) = tcp.split();
        let mut reader = BufReader::new(reader);
        let mut writer = BufWriter::new(writer);

        select! {
            
        }
        Ok(())
    }

}