use std::{io, collections::HashMap};

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_int() -> i32 {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, i32)
}

fn read_str() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    input_line.trim_matches('\n').to_string()
}

fn read_person() -> Vec<String> {    
    read_str().split(' ').map(|x| {x.to_string()}).collect()
}

struct Formula {
    properties: HashMap<u32, String>
}

impl Formula {
    fn new(formula_str: &str, dic: &HashMap<String,u32> ) -> Formula {
        
        let properties = formula_str
            .split(" AND ")
            .filter_map(|condition| {
                condition.split_once('=').map(|(prop, val)| {
                    (dic.get(&prop.trim().to_string()).unwrap_or(&99).clone(), val.trim().to_string())
                })
            })
            .collect();

        Formula { properties }
    }

    fn matches(&self, person: &Vec<String>) -> bool {
        for (&idx, val) in &self.properties {
            if person.get(idx as usize).map_or(true, |p| p != val) {
                return false;
            }
        }
        true
    }
}

fn main() {
    let mut properties: HashMap<String,u32>  = HashMap::new();
    let mut persons: Vec<Vec<String>> = Vec::new();

    for i in 0..read_int() as usize {
        properties.insert(read_str(), (i + 1) as u32);
    }

    for _ in 0..read_int() as usize {
        persons.push(read_person());
    }

    for _ in 0..read_int() as usize {
        let mut cmpt = 0u32;
        let formula = Formula::new(&read_str(), &properties);

        persons.iter().for_each(|x| cmpt += formula.matches(x) as u32);

        println!("{}", cmpt);
    }
}
