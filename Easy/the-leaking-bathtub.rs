use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_int() -> i32 {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, i32)
}

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, String)
}

fn sort_leaks(leaks: &mut Vec<[i32; 2]>) {
    let mut sorted = false;
    while !sorted {
        sorted = true;
        for i in 1..leaks.len() {
            if leaks[i-1][0] > leaks[i][0] {
                leaks.swap(i-1, i);
                sorted = false;
            }
        }
    }
}

fn main() {
    
    let s: i32 = read_int();                 // surface area (cm²)
    let h: i32 = read_int();                 // height of the bathtub (cm)
    let mut flow: i32 = read_int() * 1000;   // flow (cm³/min)

    // List leaks
    let n = read_int();
    let mut leaks = Vec::with_capacity(n as usize);
    for _ in 0..n {
        let values: Vec<i32> = read_string()
            .split_whitespace()
            .map(|x| x.parse().expect("Invalid leak data"))
            .collect();
        leaks.push([values[0], values[1] * 1000]);
    }
    sort_leaks(&mut leaks);
    
    // Calculate filling time
    let mut time = 0.0; // time (s)
    let mut filled = 0; // height filled (cm)
    for leak in leaks.iter() {
        time += 60.0 * (leak[0] - filled) as f64 * s as f64 / flow as f64;
        filled = leak[0];
        flow  -= leak[1];
        
        if flow <= 0 {
            println!("Impossible, {} cm.", filled);
            return;
        }
    }
    
    // Add time to fill remaining height
    time += 60.0 * (h - filled) as f64 * s as f64 / flow as f64;
    
    // Convert to HH:MM:SS
    let hours = (time / 3600.0) as i32;
    let minutes = ((time - hours as f64 * 3600.0) / 60.0) as i32;
    let seconds = (time - hours as f64 * 3600.0 - minutes as f64 * 60.0) as i32;
    
    println!("{:02}:{:02}:{:02}", hours, minutes, seconds);
}