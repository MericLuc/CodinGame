use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

#[derive(Debug, Clone, PartialEq)]
enum Direction {
    NorthWest,
    NorthEast,
    SouthWest,
    SouthEast,
}

impl Direction {
    fn from(val: u8) -> Self {
        match val {
            0 => Direction::NorthWest,
            1 => Direction::NorthEast,
            2 => Direction::SouthWest,
            _ => Direction::SouthEast,
        }
    }

    fn offset(&self) -> (i8, i8) {
        match self {
            Direction::NorthWest => (-1, -1),
            Direction::NorthEast => (-1, 1),
            Direction::SouthWest => (1, -1),
            Direction::SouthEast => (1, 1),
        }
    }
}

const ROWS: usize = 9;
const COLS: usize = 17;
const SYMBOLS: [char; 15] = [' ', '.', 'o', '+', '=', '*', 'B', 'O', 
                             'X', '@', '%', '&', '#', '/', '^'];

fn pos_update(from: &mut (i8, i8), dir: &Direction) {
    let (dx, dy) = dir.offset();
    *from = (
        (from.0 + dx).clamp(0, (ROWS - 1) as i8), 
        (from.1 + dy).clamp(0, (COLS - 1) as i8));
}

fn main() {
    let mut grid = vec![vec![0; COLS]; ROWS];
    let mut pos: (i8, i8) = (4, 8);

    parse_input!(String).split(':').for_each(|byte_str| {
        let byte = u8::from_str_radix(byte_str, 16).expect("Invalid hex");
        for i in 0..4 {
            let bits = (byte >> (i * 2)) & 0b11;
            pos_update(&mut pos, &Direction::from(bits));
            grid[pos.0 as usize][pos.1 as usize] += 1;
        }
    });

    println!("+---[CODINGAME]---+");
    for (i, row) in grid.iter().enumerate() {
        print!("|");
        for (j, &cell) in row.iter().enumerate() {
            if (i, j) == (pos.0 as usize, pos.1 as usize) {
                print!("E");
            }
            else if (i, j) == (4, 8) {
                print!("S");
            }
            else {
                print!("{}", SYMBOLS[cell % 15]);
            }
        }
        println!("|");
    }
    println!("+-----------------+");
}
