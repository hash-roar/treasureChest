mod proxy;
mod config;
mod connection;
mod timer;

use std::env;

use color_eyre::Result;
use crate::config::Config;
use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    net::TcpListener,
    sync::broadcast,
};

#[tokio::main]
async fn  main() ->Result<()>{
    env::set_var("RUST_LOG", "debug");
    dotenv::dotenv().ok();
    
    let cfg = Config::init()?;
    Ok(())
}

// #[tokio::main]
// async fn main() {
//     let listener = TcpListener::bind("127.0.0.1:8080").await.unwrap();
//     let (tx, _rx) = broadcast::channel(10);

//     loop {
//         let (mut socket, _addr) = listener.accept().await.unwrap();

//         let tx = tx.clone();
//         let mut rx = tx.subscribe();
//         tokio::spawn(async move {
//             let (reader, mut writer) = socket.split();
//             let mut reader = BufReader::new(reader);
//             let mut line = String::new();
//             loop {
//                 let byte_read = match reader.read_line(&mut line).await {
//                     Ok(n) => n,
//                     Err(err) => {
//                         print!("{}", err);
//                         0
//                     }
//                 };
//                 if byte_read == 0 {
//                     break;
//                 }

//                 tx.send(line.clone()).unwrap();

//                 let msg = rx.recv().await.unwrap();
//                 writer.write_all(msg.as_bytes()).await.unwrap();
//                 line.clear();
//             }
//         });
//     }
// }
