use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn to_decimal(str: &str) -> u32 {
    str.chars()
        .map(|c| match c {
            '1'..='9' => c.to_digit(10).unwrap(),
            'A' => 10,
            _ => panic!("Invalid decimary symbol '{}'", c),
        })
        .fold(0, |acc, digit| acc * 10 + digit)
}

fn to_decimary(mut decimal: u32) -> String {
    let mut res = String::new();
    let mut digit: u32;
    while decimal > 0 {
        match decimal % 10 {
            0 => { 
                res.push('A');
                digit = 10;
            },
            d => {
                res.push(char::from_digit(d, 10).unwrap());
                digit = d;
            },
        };
        decimal = (decimal - digit) / 10;
    }
    res.chars().rev().collect()
}
fn main() {
    let _ = read_string();
    println!("{}", to_decimary(read_string().split_whitespace().map(to_decimal).sum::<u32>()));
}
