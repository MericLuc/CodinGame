use std::io;
use std::collections::HashMap;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn parse_offer(offer: String, into: &mut HashMap<String, u32>) {
    let parts: Vec<&str> = offer.split(" = ").collect();

    if 2 != parts.len() {
        panic!("Invalid offering format");
    }

    let price = parts[0].trim_start_matches("$").parse::<u32>().unwrap_or(0);
    let vegetables: Vec<String> = parts[1].chars().filter(|&c| !c.is_whitespace())
    .map(|c| c.to_string())
    .collect();

    for vegetable in vegetables {
        into.insert(vegetable.clone(), price);
    }
}

fn main() {
    let mut offers: HashMap<String, u32> = HashMap::new();
    let mut res = 0;

    for _ in 0..parse_input!(i32) as usize {
        parse_offer(parse_input!(String), &mut offers);
    }

    for _ in 0..parse_input!(i32) as usize {
        res += parse_input!(String).chars().filter_map(|c| offers.get(&c.to_string()))
        .sum::<u32>();
    }

    println!("${}", res.to_string().as_bytes().rchunks(3).rev().map(std::str::from_utf8).collect::<Result<Vec<&str>, _>>().unwrap().join(","));
}
