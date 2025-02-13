use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn is_prime(num: u64) -> bool {
    if num < 2 {
        return false;
    }
    for i in 2..=((num as f64).sqrt() as u64) {
        if num % i == 0 {
            return false;
        }
    }
    true
}

fn find_prime_twins(start: u64) -> (u64, u64) {
    let mut num = start + 1;
    loop {
        if is_prime(num) && is_prime(num + 2) {
            return (num, num + 2);
        }
        num += 1;
    }
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    
    let (a, b) = find_prime_twins(parse_input!(input_line, u64));

    println!("{} {}", a, b);
}
