use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let m: usize = parse_input!(input, usize);

    for _ in 0..m {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let parts: Vec<&str> = input.trim().split("/").collect();
        
        let ip = parts[0];
        let cidr: u32 = parts[1].parse().unwrap();
        let var_part = 32 - cidr; 
        
        let ip_bins: Vec<String> = ip.split('.')
            .map(|s| format!("{:08b}", s.parse::<u8>().unwrap()))
            .collect();
        let ip_bin_str = ip_bins.join("");
                
        if var_part == 0 {
            println!("valid 1");
        } else {
            let var_part_str = &ip_bin_str[ip_bin_str.len() - var_part as usize..];
            if var_part_str.chars().all(|c| c == '0') {
                println!("valid {}", 2u64.pow(var_part));
            } else {
                let var_part = ip_bin_str.chars().rev().take_while(|&c| c == '0').count();
                let cidr = 32 - var_part;
                println!("invalid {}/{} {}", ip, cidr, 2u64.pow(var_part as u32));
            }
        }
    }
}