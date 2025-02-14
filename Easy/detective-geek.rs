use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {
    let months = ["jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"];

    let time = read_string().chars().map(|c| { 
        match c {
            '#' => 1,
            _ => 0,
        }
    }).fold(0, |acc, x| 2 * acc + x);

    let mut addr = String::new();
    for word in read_string().split_whitespace() {
        let (a, b) = word.split_at(word.len() / 2);

        addr.push(char::from(u8::from_str_radix(format!("{}{}", 
        char::from_digit(months.iter().position(|&x| x == a).unwrap() as u32, 12).unwrap(),
        char::from_digit(months.iter().position(|&x| x == b).unwrap() as u32, 12).unwrap()).as_str(), 12).unwrap())); 
    }; 

    println!("{:02}:{:02}\n{}", time/100, time % 100, addr);
}
