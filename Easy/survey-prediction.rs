use std::io;
use std::collections::HashMap;

type Gender = String;
type Genre = String;

struct Range {
    min: Option<u8>,
    max: Option<u8>,
}

impl Range {
    fn new() -> Self {
        Self { min: None, max: None }
    }

    fn contains(&self, entry: u8) -> bool {
        match (self.min, self.max) {
            (Some(min), Some(max)) => entry >= min && entry <= max,
            _ => false,
        }
    }

    fn update(&mut self, entry: u8) {
        match (self.min, self.max) {
            (None, None) => {
                self.min = Some(entry);
                self.max = Some(entry);
            },
            (Some(min), Some(max)) => {
                if entry < min {
                    self.min = Some(entry);
                } 
                if entry > max {
                    self.max = Some(entry);
                }
            },
            _ => {},
        }
    }
}

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn parse_entry(entry: String, into: &mut HashMap<Gender, HashMap<Genre, Range>>, or: &mut Vec<(Gender, u8)> ) {
    let parts: Vec<&str> = entry.split(" ").collect();
    match parts.len() {
        3 => {
            let (age, gender, genre) = 
            (parts[0].parse::<u8>().unwrap(), 
             parts[1].to_string(), 
             parts[2].to_string());

            let gender_map = into.entry(gender).or_insert_with(HashMap::new);
            let range = gender_map.entry(genre).or_insert_with(Range::new);
            
            range.update(age);
        },
        2 => or.push((parts[1].to_string(), parts[0].parse::<u8>().unwrap())),
        _ => panic!("Invalid entry: '{}'", entry),
    }
}

fn main() {
    let mut stats: HashMap<Gender, HashMap<Genre, Range>> = Default::default();
    let mut unclassified : Vec<(Gender, u8)>  = vec![];

    for _ in 0..parse_input!(usize)  {
        parse_entry(parse_input!(String), &mut stats, &mut unclassified);
    }

    for (gender, age) in unclassified {
        let mut found = false;
        
        if let Some(genres) = stats.get(&gender) {
            for (genre, range) in genres {
                if range.contains(age) {
                    println!("{}", genre);
                    found = true;
                    break;
                }
            }
        }
        
        if !found {
            println!("None");
        }
    }
}
