use std::{net::{ SocketAddr}, sync::Mutex, fmt::{Display, self}};

use color_eyre::Result;
use tokio::{sync::oneshot,net::{TcpStream}, io::{BufReader, BufWriter, copy, copy_bidirectional}, select};
use tracing::{instrument,warn, info};


#[derive(Debug)]
pub enum ProxyState {
    Init,
    FromConnSet,
    ToConnSetting,
    Established,
}

impl  ProxyState {
    fn to_string(&self)-> &str{
        match self {
            &ProxyState::Init=> "connection initing",
            &ProxyState::FromConnSet=>"connect from src attached",
            &ProxyState::ToConnSetting=>"connecting to the des",
            &ProxyState::Established=>"connection established",
        }
    } 
}

impl fmt::Display for ProxyState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{}",
            self.to_string()
        )
    }
}


#[derive(Debug)]
pub struct  ProxyConnection{
    pub state:Mutex<ProxyState>,
}

impl ProxyConnection {
    pub fn new()-> ProxyConnection{
        ProxyConnection{
            state: Mutex::new(ProxyState::Init)
        }
    }

    #[instrument]
     pub async fn process(& self,mut tcp:TcpStream,addr: SocketAddr,des :String) -> Result<()>{
        {
            *self.state.lock().unwrap() = ProxyState::ToConnSetting;
        }

        let mut des_stream = TcpStream::connect(&des).await?;

        {
            *self.state.lock().unwrap() = ProxyState::Established;
        }
        let (src_to_des, des_to_src)=  copy_bidirectional(&mut tcp, & mut des_stream).await?;

        info!("connection: {} ===> {}  close,copy bytes: src --> des:{},  des --> src:{}",
            addr,&des,src_to_des,des_to_src);
        Ok(())
    }

}