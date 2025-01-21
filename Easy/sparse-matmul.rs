use std::collections::HashMap;
use std::io;
use std::collections::HashSet;
use itertools::Itertools;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_matrix(entries: usize, row_wise: bool) -> HashMap<usize, HashMap<usize, f64>> {
    let mut matrix: HashMap<usize, HashMap<usize, f64>> = HashMap::new();
    for _ in 0..entries {
        let mut entry = String::new();
        io::stdin().read_line(&mut entry).unwrap();
        let inputs = entry.split_whitespace().collect::<Vec<_>>();
        
        let r = parse_input!(inputs[0], usize);
        let c = parse_input!(inputs[1], usize);
        let v = parse_input!(inputs[2], f64);

        if row_wise {
            matrix.entry(r).or_insert_with(HashMap::new).insert(c, v);
        } else {
            matrix.entry(c).or_insert_with(HashMap::new).insert(r, v);
        }
    }
    matrix
}

fn dot_product(a: &HashMap<usize, HashMap<usize, f64>>, 
               b: &HashMap<usize, HashMap<usize, f64>>, 
               i: usize, k: usize) -> f64 {
    match (a.get(&i), b.get(&k)) {
        (Some(row_a), Some(col_b)) => {
            
            let keys_a: HashSet<_> = row_a.keys().collect();
            let keys_b: HashSet<_> = col_b.keys().collect();
            
            keys_a.intersection(&keys_b)
                 .map(|&j| row_a[j] * col_b[j])
                 .sum()
        }
        _ => 0.0
    }
}

// Damn stupid formatting
fn format_number(num: &f64) -> String {
    if (num - num.round()).abs() < f64::EPSILON {
        format!("{:.1}", num) 
    } else {
        format!("{}", num) 
    }
}


fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let inputs = input_line.split_whitespace().collect::<Vec<_>>();
    
    let a_entries = parse_input!(inputs[0], usize);
    let b_entries = parse_input!(inputs[1], usize);
    let a = read_matrix(a_entries, true);
    let b = read_matrix(b_entries, false);

    for i in a.keys().sorted() {
        for k in b.keys().sorted() {
            let dot_prod = dot_product(&a, &b, *i, *k);
            if dot_prod != 0.0 {
                println!("{} {} {}", i, k, format_number(&dot_prod));
            }
        }
    }
}