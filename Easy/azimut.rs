use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {

    let dirs = ["N", "NE", "E", "SE", "S", "SW", "W", "NW"];
    let start_direction = read_string();
    let mut idx = dirs.iter()
        .position(|&dir| dir == start_direction)
        .expect("Invalid direction");

    for _ in 0..read_string().parse::<i32>().unwrap() {
        match read_string().as_str() {
            "RIGHT" => idx += 1,
            "LEFT" => idx += 7,
            "BACK" => idx += 4,
            _ => (),
        };
    }

    println!("{}", dirs[idx % 8]);
}
