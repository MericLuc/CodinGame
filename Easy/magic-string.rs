use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn process(list: &[String]) {
    let mut sml = false;
    let mut srt = list.to_vec();
    srt.sort();
    
    let s1 = &srt[srt.len() / 2 - 1];
    let s2 = &srt[srt.len() / 2];
    
    let len1 = s1.len();
    let len2 = s2.len();
    
    let s1_extended = if len1 >= len2 {
        s1.clone()
    } else {
        format!("{}{}", s1, ".".repeat(len2 - len1))
    };
    
    let s2_extended = if len2 >= len1 {
        s2.clone()
    } else {
        format!("{}{}", s2, ".".repeat(len1 - len2))
    };
    
    let len = std::cmp::max(len1, len2);
    let mut arr = vec!['\0'; len];
    
    let s1_chars: Vec<char> = s1_extended.chars().collect();
    let s2_chars: Vec<char> = s2_extended.chars().collect();
    
    for i in 0..len {
        let c1 = s1_chars[i];
        let c2 = s2_chars[i];
        
        if c1 == c2 {
            if !sml {
                arr[i] = c1;
                if len2 > len1 && i + 1 == len1 {
                    break;
                }
            } else {
                arr[i] = ((c1 as u8) + 1) as char;
                break;
            }
        } else {
            if !sml {
                if c1 < c2 && i == len - 1 {
                    arr[i] = c1;
                    break;
                } else if ((c1 as u8) + 1) < (c2 as u8) {
                    arr[i] = ((c1 as u8) + 1) as char;
                    break;
                } else if ((c1 as u8) + 1) == (c2 as u8) {
                    if i == len2 - 1 {
                        arr[i] = c1;
                        sml = true;
                    } else {
                        arr[i] = ((c1 as u8) + 1) as char;
                        break;
                    }
                }
            } else {
                if i == len - 1 {
                    arr[i] = c1;
                    break;
                } else {
                    if ((c1 as u8) + 1) <= b'Z' {
                        arr[i] = ((c1 as u8) + 1) as char;
                        break;
                    } else {
                        arr[i] = c1;
                    }
                }
            }
        }
    }
    
    let result: String = arr.iter()
                           .take_while(|&&c| c >= 'A')
                           .collect();
    
    println!("{}", result);
}

fn main() {
    let n = parse_input!(usize);
    let mut list = Vec::with_capacity(n);

    for _ in 0..n {
        list.push(parse_input!(String));
    }
    
    process(&list);
}
