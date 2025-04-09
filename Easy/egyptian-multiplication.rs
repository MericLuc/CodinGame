use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn main() {
    let inputs = parse_input!(String)
        .split(' ')
        .map(|x| x.parse::<i32>().unwrap_or(0))
        .collect::<Vec<_>>();

    let mut b = core::cmp::min(inputs[0], inputs[1]);
    let mut a = core::cmp::max(inputs[0], inputs[1]);

    let mut decomp = Vec::new();

    println!("{} * {}", a, b);

    while 0 != b {
        match b % 2 {
            0 => {
                a = a * 2;
                b = (b + 1)/2;
            },
            _ => {
                decomp.push(a);
                b = b - 1;
            },
        }
        let decomp_str = if decomp.is_empty() {
            String::new()
        } else {
            format!(" + {}", decomp.iter()
                .map(ToString::to_string)
                .collect::<Vec<_>>()
                .join(" + "))
        };
        
        println!("= {} * {}{}", a, b, decomp_str);
    }
    println!("= {}", decomp.iter().sum::<i32>());
}
