use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    let ny = parse_input!(input_line, i32);
    let nx: i32 = 3 * (ny - 1) / 2 + 1;

    let dy: f64 = 2.0 / (ny - 1) as f64;
    let dx: f64 = 3.0 / (nx - 1) as f64;

    let y: Vec<f64> = (0..ny).map(|i| 1.0 - (i as f64 * dy)).collect();
    let x: Vec<f64> = (0..nx).map(|i| -2.0 + (i as f64 * dx)).collect();

    let f = |cr: f64, ci: f64| -> char {
        let mut zr = 0.0; 
        let mut zi = 0.0;
        
        for _ in 0..10 {
            let zr_new = zr * zr - zi * zi + cr;
            let zi_new = 2.0 * zr * zi + ci;
            zr = zr_new;
            zi = zi_new;
        }
        
        if (zr * zr + zi * zi).sqrt() <= 1.0 { '*' } else { ' ' }
    };

    for yi in y {
        let line: String = x.iter()
            .map(|&xi| f(xi, yi))
            .collect();
        println!("{}", line);
    }
}