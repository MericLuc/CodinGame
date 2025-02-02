use std::io;
use std::collections::HashMap;
use itertools::Itertools;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn read_int() -> u32 {
    parse_input!(read_string(), u32)
}

#[derive(Clone, Copy)]
struct Coord {
    x: u32,
    y: u32,
}

struct GameState {
    w: u32,
    h: u32,
    cells: Vec<String>,
    prev: Vec<String>,
    played: Vec<String>,
    pts: HashMap<char, u32>,
    words: HashMap<String, u32>,
}

impl GameState {
    fn get_value_l(&self, x: u32, y: u32) -> usize {
        let x = x as usize;
        let y = y as usize;

        // Fixed: Swapped x and y indices
        if '.' == self.prev[y].chars().nth(x).unwrap() {
            match self.cells[y].chars().nth(x).unwrap() {
                'l' => 2,
                'L' => 3,
                _ => 1,
            }
        } else {
            1
        }
    }

    fn get_value_w(&self, x: u32, y: u32) -> usize {
        let x = x as usize;
        let y = y as usize;

        if self.prev[y].chars().nth(x).unwrap() == '.' {
            match self.cells[y].chars().nth(x).unwrap() {
                'w' => 2,
                'W' => 3,
                _ => 1,
            }
        } else {
            1
        }
    }

    fn compute_h(&mut self, c: &Coord) {
        let mut x_min = c.x;
        let mut x_max = c.x;
        let y = c.y;
        let mut k = 1;
        let mut score = 0;
        
        while x_min > 0 && self.played[y as usize].chars().nth((x_min-1) as usize).unwrap() != '.' {
            x_min -= 1;
        }
        while x_max < self.w-1 && self.played[y as usize].chars().nth((x_max+1) as usize).unwrap() != '.' {
            x_max += 1;
        }
        
        if x_min != x_max {
            let mut word = String::new();
            for x in x_min..=x_max {
                let ch = self.played[y as usize].chars().nth(x as usize).unwrap();
                word.push(ch);
                score += self.get_value_l(x, y) * (*self.pts.get(&ch).unwrap_or(&0) as usize);
                k *= self.get_value_w(x, y);
            }
            self.words.insert(word, (k * score) as u32);
        }
    }

    fn compute_v(&mut self, c: &Coord) {
        let mut y_min = c.y;
        let mut y_max = c.y;
        let x = c.x;
        let mut k = 1;
        let mut score = 0;
        
        while y_min > 0 && self.played[(y_min-1) as usize].chars().nth(x as usize).unwrap() != '.' {
            y_min -= 1;
        }
        while y_max < self.h-1 && self.played[(y_max+1) as usize].chars().nth(x as usize).unwrap() != '.' {
            y_max += 1;
        }
        
        if y_min != y_max {
            let mut word = String::new();
            for y in y_min..=y_max {
                let ch = self.played[y as usize].chars().nth(x as usize).unwrap();
                word.push(ch);
                score += self.get_value_l(x, y) * (*self.pts.get(&ch).unwrap_or(&0) as usize);
                k *= self.get_value_w(x, y);
            }
            self.words.insert(word, (k * score) as u32);
        }
    }
}

fn main() {
    // Tiles
    let mut pts: HashMap<_, u32> = HashMap::new();
    for _ in 0..read_int() as usize {
        let input_line = read_string();
        let inputs: Vec<&str> = input_line.split(" ").collect();
        pts.insert(inputs[0].chars().next().unwrap(), parse_input!(inputs[1], u32));
    }

    // Board dimensions
    let input_line = read_string();
    let dims: Vec<&str> = input_line.split_whitespace().collect();
    // Fixed: Proper parsing of dimensions
    let w = parse_input!(dims[0], u32);
    let h = parse_input!(dims[1], u32);
    
    // Board states
    let mut cells = Vec::new();
    let mut prev = Vec::new();
    let mut played = Vec::new();
    
    for _ in 0..h {
        cells.push(read_string());
    }
    for _ in 0..h {
        prev.push(read_string());
    }
    for _ in 0..h {
        played.push(read_string());
    }

    // Check new tiles
    let mut tiles = Vec::new();
    for y in 0..h {
        for x in 0..w {
            if prev[y as usize].chars().nth(x as usize) != played[y as usize].chars().nth(x as usize) {
                tiles.push(Coord { x, y });
            }
        }
    }
    
    let mut game = GameState {
        w,
        h,
        cells,
        prev,
        played,
        pts,
        words: HashMap::new(),
    };
    
    // Compute scores
    if tiles.len() == 1 {
        game.compute_h(&tiles[0]);
        game.compute_v(&tiles[0]);
    } else if tiles[0].y == tiles[1].y {
        game.compute_h(&tiles[0]);
        for c in &tiles {
            game.compute_v(c);
        }
    } else {
        game.compute_v(&tiles[0]);
        for c in &tiles {
            game.compute_h(c);
        }
    }
    
    let mut score = 0;
    for (word, points) in game.words.iter().sorted() {
        score += points;
        println!("{} {}", word, points);
    }
    
    if tiles.len() == 7 {
        score += 50;
        println!("Bonus 50");
    }
    
    println!("Total {}", score);
}