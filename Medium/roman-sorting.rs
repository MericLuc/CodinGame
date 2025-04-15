use std::io;
use std::collections::BTreeMap;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

mod roman {
    pub fn from_int(decimal: u32) -> String {
        let mut res = String::new();
        let mut remaining = decimal;

        for place in (0..4).rev() {
            let divisor = 10_u32.pow(place as u32);
            let digit = (remaining / divisor) as u8;
            remaining %= divisor;
            
            res.push_str(&from_digit(digit, place));
        }
        
        res
    }

    fn from_digit(digit: u8, place: usize) -> String {
        const UNITS: [&str; 10] = ["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"];
        const TENS: [&str; 10] = ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"];
        const HUNDREDS: [&str; 10] = ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"];
        const THOUSANDS: [&str; 10] = ["", "M", "MM", "MMM", "", "", "", "", "", ""];
    
        match place {
            0 => UNITS[digit as usize].to_string(),
            1 => TENS[digit as usize].to_string(),
            2 => HUNDREDS[digit as usize].to_string(),
            _ => THOUSANDS[digit as usize].to_string()
        }
    }
}

fn main() {
    let mut res: BTreeMap<String, u32> = BTreeMap::new();

    for _ in 0..parse_input!(usize) {
        let x = parse_input!(u32);
        res.insert(roman::from_int(x), x);
    }

    println!("{}", res.values().map(|x| x.to_string()).collect::<Vec<String>>().join(" "));
}
