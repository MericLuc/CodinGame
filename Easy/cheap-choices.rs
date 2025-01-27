use std::io;
use std::collections::{ HashMap, BTreeMap, BTreeSet };

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn parse_input(input: &str) -> Option<(String, String, u32)> {
    let mut parts = input.split_whitespace();

    let category = parts.next()?.to_string();
    let size = parts.next()?.to_string();
    let price = parts.next()?.parse::<u32>().ok()?;

    return Some((category, size, price));
}

fn parse_order(input: &str) -> Option<(String, String)> {
    let mut parts = input.split_whitespace();

    let category = parts.next()?.to_string();
    let size = parts.next()?.to_string();

    return Some((category, size));
}


fn main() {
    let mut inventory: HashMap<String, HashMap<String, BTreeSet<u32>>> = HashMap::new();

    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let c = parse_input!(input_line, i32);

    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let p = parse_input!(input_line, i32);

    for _ in 0..c as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let item = input_line.trim_matches('\n').to_string();
        
        if let Some((category, size, price)) = parse_input(&item) {
            let elems_map = inventory.entry(category).or_insert_with(HashMap::new);
            let prices_set = elems_map.entry(size).or_insert_with(BTreeSet::new) ;
            prices_set.insert(price);
        }
    }

    for _ in 0..p as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let order = input_line.trim_matches('\n').to_string();

        let mut reply = "NONE".to_string();
        if let Some((category, size)) = parse_order(&order) {

            if let Some(elems_map) = inventory.get_mut(&category) {
                if let Some(prices_set) = elems_map.get_mut(&size) {
                    if let Some(first) = prices_set.pop_first() {
                        reply = first.to_string();
                    }
                }
            }
        }

        println!("{}", reply);
    }
}
