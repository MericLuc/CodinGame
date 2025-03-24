use std::fmt;
use std::str::FromStr;
use std::cmp::Ordering;
use std::io;

#[derive(Debug, PartialEq, Eq, Clone)]
struct Timestamp {
    minutes: u32,
    seconds: u32,
}

impl Timestamp {
    fn new(minutes: u32, seconds: u32) -> Self {
        if seconds > 59 {
            panic!("Seconds must be between 0 and 59");
        }

        Self { minutes, seconds }
    }

    fn as_seconds(&self) -> i32 {
        self.minutes as i32 * 60 + self.seconds as i32
    }

    fn from_seconds(seconds: i32) -> Self {

        if 0 >= seconds {
            return Timestamp::new(0,0);
        }

        let minutes = (seconds / 60) as u32;
        let seconds = (seconds % 60) as u32;

        Timestamp::new(minutes, seconds)
    }
}

impl FromStr for Timestamp {
    type Err = &'static str;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let parts: Vec<&str> = s.split(':').collect();
        
        if parts.len() != 2 {
            return Err("Invalid format.");
        }

        let minutes = parts[0].parse().map_err(|_| "Invalid minutes")?;
        let seconds = parts[1].parse().map_err(|_| "Invalid seconds")?;

        Ok( Timestamp::new(minutes, seconds) )
    }
}

impl fmt::Display for Timestamp {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}:{:02}", self.minutes, self.seconds)
    }
}

impl PartialOrd for Timestamp {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.as_seconds().cmp(&other.as_seconds()))
    }
}

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_int() -> i32 {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, i32)
}

fn read_timestamp() -> Timestamp {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string().parse().unwrap_or(Timestamp::new(0,0))
}

fn main() {
    let mut t_stop = Timestamp::new(0,0);
    let mut players = 1;

    for i in 0..read_int() as u32 {
        let t_cur = read_timestamp();

        if t_cur < t_stop {
            break;
        }

        if 6 == i {
            t_stop = t_cur;
            break;
        }

        t_stop = Timestamp::from_seconds(t_cur.as_seconds() - (256 / (2 as i32).pow(i)));
        players = players + 1;
    }

    println!("{}", match players {
        1 => "NO GAME".to_string(),
        _ => t_stop.to_string(),
    });
}
