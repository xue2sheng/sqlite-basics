use rusqlite::{Connection, Result};

#[allow(dead_code)]
#[derive(Debug)]
struct Item {
    name: String,
    value: u32,
}

fn main() -> Result<()> {
    let conn = Connection::open("test02.db")?;
    let mut stmt = conn.prepare("SELECT * FROM tblone;")?;
    let items = stmt.query_map([], |row| { Ok(Item { name: row.get(0)?, value: row.get(1)?, }) })?;
    for item in items { println!("{:?}", item.unwrap()); }
    Ok(())
}
