use std::io;
use std::collections::HashSet;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn main() {
    let mut cache = HashSet::new();
    let total = parse_input!(usize);
    let mut alphabet = Vec::new();
    alphabet.reserve(total);

    for _ in 0..total {
        alphabet.push(parse_input!(String));
    }

    let seq: Vec<String> = (0..(1 << total))
    .map(|number| format!("{:0total$b}", number))
    .collect();

    for (a, b) in alphabet.iter().zip(alphabet.iter().skip(1)) {
        for bin in &seq {
            let entry = bin.replace('0', a).replace('1', b);
            if !cache.contains(&entry) {
                cache.insert(entry.clone());
                println!("{entry}");
            }
        }
    }
}
