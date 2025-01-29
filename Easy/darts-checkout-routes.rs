use std::io;
use std::collections::VecDeque;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_int() -> i32 {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, i32)
}

#[derive(Clone, Copy)]
pub enum Segment {
    Single(u8),
    Double(u8),
    Treble(u8)
}

impl Segment {
    pub fn value(&self) -> Option<u32> {
        match self {
            Segment::Single(n) => {
                if *n <= 20 || *n == 25 {
                    Some(*n as u32)
                } else {
                    None
                }
            }
            Segment::Double(n) => {
                if *n <= 20 || *n == 25 {
                    Some((*n as u32) * 2)
                } else {
                    None
                }
            }
            Segment::Treble(n) => {
                if *n <= 20 && *n != 25 {
                    Some((*n as u32) * 3)
                } else {
                    None
                }
            }
        }
    }
}

#[derive(Clone)]
struct State {
    target_score: i32,
    darts_left: i32,
    route: Vec<Segment>
}

impl State {
    fn new(goal: i32, left: i32) -> State {
        State { target_score: goal, darts_left : left, route : Vec::new() }
    }

    fn push(&self, segment: &Segment) -> State {
        let mut ret = self.clone();
        ret.route.push(*segment);
        ret.target_score -= segment.value().unwrap() as i32;
        ret.darts_left -= 1;

        ret
    }

    fn is_valid(&self) -> bool {
        (0 <= self.target_score) && (0 <= self.darts_left)
    }

    fn is_final(&self) -> bool {
        (0 == self.target_score) && matches!(self.route.last(), Some(Segment::Double(_)))    
    }
}

fn main() {
    let score = read_int();
    let darts = read_int();

    let mut singles = Vec::new();
    let mut doubles = Vec::new();
    let mut trebles = Vec::new();

    for i in 1..=20 {
        singles.push(Segment::Single(i));
        doubles.push(Segment::Double(i));
        trebles.push(Segment::Treble(i));
    }
    singles.push(Segment::Single(25));
    doubles.push(Segment::Double(25));

    let mut queue = VecDeque::new();
    queue.push_back(State::new(score, darts));
    
    let mut ret = 0;

    while let Some(state) = queue.pop_front() {
        if state.is_final() {
            ret += 1;
            continue;
        }

        if !state.is_valid() {
            continue;
        }

        if state.darts_left == 1 {
            for double in &doubles {
                let new_state = state.push(double);
                if new_state.is_valid() {
                    queue.push_back(new_state);
                }
            }
            continue;
        }

        for segment in singles.iter().chain(doubles.iter()).chain(trebles.iter()) {
            let new_state = state.push(segment);
            if new_state.is_valid() {
                queue.push_back(new_state);
            }
        }
    }

    println!("{}", ret);
}
