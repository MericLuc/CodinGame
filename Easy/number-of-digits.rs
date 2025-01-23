use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}


fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let n = parse_input!(input_line, i64);
    
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let k = parse_input!(input_line, i64);

    let mut res = 0i64;
    let mut f = 1i64;

    while n >= f {
        let high = n / (f * 10);
        let cur = (n / f) % 10;
        let low = n % f;
        
        // (high * f)             : digit combinations above current position
        // (cur == k) * (low + 1) : extra occurrences if the current digit exactly matches k
        // (cur > k) * f          : extra occurrences if the current digit is larger than k
        res += high * f + (cur == k) as i64 * (low + 1) + (cur > k) as i64 * f;
        f *= 10;
    }
    println!("{}", res);
}
