use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

type Grid<T> = Vec<Vec<T>>;

fn search(pattern: &str, grid: &Grid<char>) -> Vec<(usize, usize)> {
    const DIRS: [(i8, i8); 8] = [
        (0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)
    ];

    let mut ret = Vec::new();

    let pattern_chars: Vec<char> = pattern.chars().collect();
    let first_char = pattern_chars[0];
    let size = grid.len();
    
    for (x, y) in (0..size)
        .flat_map(|i| (0..size).map(move |j| (i, j))) {

        if grid[x][y] != first_char {
            continue;
        }

        for &(dx, dy) in &DIRS {
            ret.push((x, y));
            let (mut cur_x, mut cur_y) = (x as i8, y as i8);    
            for k in 1..pattern_chars.len() {
                cur_x += dx;
                cur_y += dy;
                        
                if cur_x < 0 || cur_x >= size as i8 || 
                    cur_y < 0 || cur_y >= size as i8 {
                    ret.clear();
                    break;
                }
                        
                if grid[cur_x as usize][cur_y as usize] != pattern_chars[k] {
                    ret.clear();
                    break;
                }
                ret.push((cur_x as usize, cur_y as usize));
            }

            if !ret.is_empty() {
                return ret;
            }
         }
     }

    ret
}

fn main() {
    let size = parse_input!(usize);
    let mut grid: Grid<char> = vec![Vec::new(); size];
    let mut states: Grid<bool> = vec![vec![false; size]; size];

    for i in 0..size {
        grid[i] = parse_input!(String).chars().collect();
    }

    for word in parse_input!(String)
        .split_whitespace()
        .map(|x| x.to_uppercase()) {
        for (x, y) in search(&word, &grid) {
            states[x][y] = true;
        }
    }

    for (i, row) in grid.iter().enumerate() {
        for (j, &cell) in row.iter().enumerate() {
            print!("{}", match states[i][j] { 
                true => cell,
                false => ' ', 
            });
        }
        println!("");
    }
}
