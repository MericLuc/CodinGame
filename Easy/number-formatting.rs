use std::io;

fn format_number(str: String) -> String {    
    let decimal_pos = str.find('.').unwrap();
    let before = &str[..decimal_pos].trim_start_matches('0');
    let after = &str[decimal_pos + 1..].trim_end_matches('0');

    let filled = format!("{}{}{}{}", 
        "x".repeat(9 - before.len()),
        before,
        after,
        "x".repeat(6 - after.len())
    );
    
    let mut result = String::new();
    
    for (i, marker) in (0..filled.len()).step_by(3).zip( [",", ",", ".", ".", ""]) {
        result.push_str(&filled[i..i+3]);
        result.push_str(marker);
    }
    
    result
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    let mut n = input_line.trim_matches('\n').replace('x', "0").to_string();
    n.retain(|c: char| c.is_digit(10));
    n.insert(9, '.');
    
    println!("{}", format_number( format!("{:.6}", n.parse::<f64>().unwrap()/ 2f64) ));
}
