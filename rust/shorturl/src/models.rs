use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct Url {
    pub id: i32,
    pub base_url: String,
    pub suffix_url: String,
    pub full_url: String,
    pub short_code: String,
    pub expiration_date: String,
    pub click_times: i64,
}

