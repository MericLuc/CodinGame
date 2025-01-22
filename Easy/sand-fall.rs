use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn create_bucket(h: usize, w: usize) -> Vec<String> {
    let mut bucket = Vec::with_capacity(h + 1);
    
    let mut pattern: String = String::with_capacity(w + 2);
    pattern.push('|');
    pattern.push_str(&" ".repeat(w));
    pattern.push('|');
    for _ in 0..h {
        bucket.push(pattern.clone());
    }
    
    let mut pattern = String::with_capacity(w + 2);
    pattern.push('+');
    pattern.push_str(&"-".repeat(w));
    pattern.push('+');
    bucket.push(pattern);
    
    bucket
}

fn drop_into_bucket(bucket: &mut Vec<String>, elm: char, col: &mut usize) {
    let mut row: i32 = -1;
    let alpha: i32 = if elm.is_uppercase() { -1 } else { 1 };
    
    loop {
        if ' ' == bucket[(row + 1) as usize].chars().nth(*col).unwrap() {
            row += 1;
        } else if ' ' == bucket[(row + 1) as usize].chars().nth((*col as i32 + alpha) as usize).unwrap() {
            *col = (*col as i32 + alpha) as usize;
        } else if ' ' == bucket[(row + 1) as usize].chars().nth((*col as i32 - alpha) as usize).unwrap() {
            *col = (*col as i32 - alpha) as usize;
        } else {
            break;
        }
    }
    
    let chars: Vec<char> = bucket[row as usize].chars().collect();
    let new_string: String = chars.iter()
        .enumerate()
        .map(|(i, &c)| if i == *col { elm } else { c })
        .collect();
    bucket[row as usize] = new_string;
}

fn main() {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let inputs = input_line.split(" ").collect::<Vec<_>>();
    let w = parse_input!(inputs[0], usize);
    let h = parse_input!(inputs[1], usize);

    let mut bucket = create_bucket(h, w);

    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let n = parse_input!(input_line, i32);

    for i in 0..n as usize {
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        let inputs = input_line.split(" ").collect::<Vec<_>>();
        let s = inputs[0].trim().to_string();
        let p = parse_input!(inputs[1], usize);

        drop_into_bucket(&mut bucket, s.chars().next().unwrap(), &mut (p + 1));
    }

    bucket.into_iter().for_each(|elm| {
        println!("{}", elm);
    });
}
