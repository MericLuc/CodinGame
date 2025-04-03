use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn main() {
    let thickness = parse_input!(usize);
    let length = parse_input!(usize);
    let turns = parse_input!(usize);

    println!(" {}{}{}", "_".repeat(thickness), (" ".to_owned() + "_".repeat(thickness*2+1).as_str()).repeat(turns / 2), (if turns % 2 == 1{" ".to_owned() + "_".repeat(thickness).as_str()} else {"".to_string()}));
    println!("|{}{}{}|", " ".repeat(thickness), ("|".to_owned() + " ".repeat(thickness*2+1).as_str()).repeat(turns / 2), (if turns % 2 == 1{"|".to_owned() + " ".repeat(thickness).as_str()} else {"".to_string()}));
    for _ in 2..length {
        println!("{}|", ("|".to_owned() + " ".repeat(thickness).as_str()).repeat(turns+1));
    }
    println!("{}{}{}", ("|".to_owned() + "_".repeat(thickness*2+1).as_str()).repeat(turns / 2), (if turns % 2 == 0{"|".to_owned() + "_".repeat(thickness).as_str()} else {"|".to_owned() + "_".repeat(thickness*2+1).as_str()}), "|");
}
