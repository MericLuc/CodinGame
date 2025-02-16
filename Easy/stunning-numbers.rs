use std::collections::HashMap;
use std::io;

fn is_strobogrammatic(number: &str) -> bool {
    let flip_map: HashMap<char, char> = [
        ('0', '0'), ('1', '1'), ('2', '2'), ('5', '5'),
        ('6', '9'), ('8', '8'), ('9', '6')
    ].iter().cloned().collect();

    let n = number.len();
    let chars: Vec<char> = number.chars().collect();
    
    for i in 0..=(n/2) {
        let c = chars[i];
        if !flip_map.contains_key(&c) || 
           chars[n - i - 1] != *flip_map.get(&c).unwrap() {
            return false;
        }
    }
    true
}

fn reverse_number(number: &str, is_odd: bool) -> String {
    let flip_map: HashMap<char, char> = [
        ('0', '0'), ('1', '1'), ('2', '2'), ('5', '5'),
        ('6', '9'), ('8', '8'), ('9', '6')
    ].iter().cloned().collect();

    let mut result: Vec<char> = number.chars().collect();
    let reversed: String = if is_odd {
        number[..number.len()-1].chars()
            .rev()
            .map(|c| flip_map[&c])
            .collect()
    } else {
        number.chars()
            .rev()
            .map(|c| flip_map[&c])
            .collect()
    };
    
    result.extend(reversed.chars());
    result.iter().collect()
}

fn next_strobogrammatic(number: &str) -> String {
    let current = if is_strobogrammatic(number) {
        println!("true");
        (number.parse::<i64>().unwrap() + 1).to_string()
    } else {
        println!("false");
        number.to_string()
    };

    let valid_digits = "0125689";
    let n = current.len();
    let mut is_odd = n % 2 == 1;
    let mut prefix = current[..(n + 1) / 2].to_string();

    loop {
        let mut i = 0;
        while i < prefix.len() {
            if valid_digits.contains(prefix.chars().nth(i).unwrap()) {
                i += 1;
            } else {
                let zeros = prefix.len() - i - 1;
                let prefix_part = &prefix[..=i];
                let incremented = prefix_part.parse::<i64>().unwrap() + 1;
                if incremented.to_string().len() > prefix_part.len() {
                    is_odd = !is_odd;
                }
                prefix = format!("{}{}", incremented, "0".repeat(zeros));
                i = 0;
            }
        }

        let result = reverse_number(&prefix, is_odd);
        if is_strobogrammatic(&result) && 
           result.parse::<i64>().unwrap() > current.parse::<i64>().unwrap() {
            return result;
        }

        let incremented = prefix.parse::<i64>().unwrap() + 1;
        if incremented.to_string().len() > prefix.len() {
            if is_odd {
                prefix = incremented.to_string();
                prefix.pop();
            } else {
                prefix = incremented.to_string();
            }
            is_odd = !is_odd;
        } else {
            prefix = incremented.to_string();
        }
    }
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let n = input_line.trim_matches('\n').to_string();

    println!("{}", next_strobogrammatic(&n));
}