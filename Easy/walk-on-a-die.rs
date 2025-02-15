use std::collections::HashMap;
use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {

    let mut rotations: HashMap<char, Vec<usize>> = HashMap::new();
    rotations.insert('U', vec![4, 1, 0, 3, 5, 2]);
    rotations.insert('L', vec![4, 5, 1, 0, 3, 2]);
    rotations.insert('D', vec![4, 3, 5, 1, 0, 2]);
    rotations.insert('R', vec![4, 0, 3, 5, 1, 2]);

    let mut die = Vec::new();
    for _ in 0..3 {
        die.extend(
            read_string()
                .trim_matches(' ').chars()
                .map(|x| x.to_digit(10).unwrap() as i32)
        );
    }

    for command in read_string().chars() {        
        if let Some(pi) = rotations.get(&command) {
            let next_die: Vec<i32> = pi.iter()
                .map(|&i| die[i])
                .collect();
            die = next_die;
        }
    }

    println!("{}", die[2]);
}