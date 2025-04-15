use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Input {
    Empty,
    Number(u8),
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Output {
    Empty,
    Filled,
    Unsolved,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
struct Coord {
    x: usize,
    y: usize,
}

#[derive(Clone, Copy, Debug)]
struct Clue {
    x: usize,
    y: usize,
    clue: u8,
}

fn is_valid(coord: Coord, n: usize) -> bool {
    coord.x < n && coord.y < n
}

fn is_inner(coord: Coord, n: usize) -> bool {
    0 < coord.x && n - 1  > coord.x && 0 < coord.y && n - 1 > coord.y
}

fn is_corner(coord: Coord, n: usize) -> bool {
    (0 == coord.x || n - 1 == coord.x) && (0 == coord.y || n - 1 == coord.y)
}

fn is_edge(coord: Coord, n: usize) -> bool {
    ((0 == coord.x|| n - 1 == coord.x) || (0 == coord.y || n - 1 == coord.y))
        && !is_corner(coord, n)
}


fn neighbourhood(coord: Coord, n: usize) -> Vec<Coord> {
    let directions = [
        (0, 0),    // itself
        (0, -1),   // N
        (1, -1),   // NE
        (1, 0),    // E
        (1, 1),    // SE
        (0, 1),    // S
        (-1, 1),   // SW
        (-1, 0),   // W
        (-1, -1),  // NW
    ];

    directions
        .iter()
        .filter_map(|&(dx, dy)| {
            let new_x = coord.x as isize + dx;
            let new_y = coord.y as isize + dy;
            
            if new_x >= 0 && new_y >= 0 {
                let new_coord = Coord { x: new_x as usize, y: new_y as usize };
                if is_valid(new_coord, n) {
                    return Some(new_coord);
                }
            }
            None
        })
        .collect()
}

fn fill(loc: Coord, value: Output, output_grid: &mut Vec<Vec<Output>>, n: usize) {
    for neighbor in neighbourhood(loc, n) {
        if output_grid[neighbor.y][neighbor.x] == Output::Unsolved {
            output_grid[neighbor.y][neighbor.x] = value;
        }
    }
}

struct NeighborhoodStats {
    clue: Clue,
    unsolved: usize,
    remaining: i32,
}

fn clue_stats(clue: Clue, output_grid: &Vec<Vec<Output>>, n: usize) -> NeighborhoodStats {
    let neighbors = neighbourhood(Coord { x: clue.x, y: clue.y }, n);
    let unsolved = neighbors
        .iter()
        .filter(|&&coord| output_grid[coord.y][coord.x] == Output::Unsolved)
        .count();
    
    let filled = neighbors
        .iter()
        .filter(|&&coord| output_grid[coord.y][coord.x] == Output::Filled)
        .count();
    
    let remaining = clue.clue as i32 - filled as i32;
    
    NeighborhoodStats { clue, unsolved, remaining }
}

fn main() {
    let n: usize = parse_input!(usize);
    let mut input_grid = vec![vec![Input::Empty; n]; n];
    let mut output_grid = vec![vec![Output::Unsolved; n]; n];
    let mut clues: Vec<Clue> = Vec::new();

    for y in 0..n {
        for (x, ch) in parse_input!(String).chars().enumerate() {
            input_grid[y][x] = match ch {
                '.' => Input::Empty,
                '0'..='9' => Input::Number((ch as u8) - b'0'),
                _ => panic!("Invalid input character"),
            };
            if let Input::Number(num) = input_grid[y][x] {
                clues.push(Clue { x, y, clue: num });
            }
        }
    }

    for &clue in &clues {
        let coord = Coord { x: clue.x, y: clue.y };
        match input_grid[clue.y][clue.x] {
            Input::Number(0) => fill(coord, Output::Empty, &mut output_grid, n),
            Input::Number(9) if is_inner(coord, n) => fill(coord, Output::Filled, &mut output_grid, n),
            Input::Number(6) if is_edge(coord, n) => fill(coord, Output::Filled, &mut output_grid, n),
            Input::Number(4) if is_corner(coord, n) => fill(coord, Output::Filled, &mut output_grid, n),
            _ => {}
        }
    }
    
    loop {
        let mut solved_indices = Vec::new();
        
        for (idx, &clue) in clues.iter().enumerate() {
            let stats = clue_stats(clue, &output_grid, n);
            let mut mark_as_solved = false;
            
            if stats.remaining as usize == stats.unsolved && stats.unsolved > 0 {
                fill(Coord { x: clue.x, y: clue.y }, Output::Filled, &mut output_grid, n);
                mark_as_solved = true;
            } else if stats.remaining == 0 && stats.unsolved > 0 {
                fill(Coord { x: clue.x, y: clue.y }, Output::Empty, &mut output_grid, n);
                mark_as_solved = true;
            }
            
            if mark_as_solved {
                solved_indices.push(idx);
            }
        }
        
        if solved_indices.is_empty() {
            break;
        }
        
        for &idx in solved_indices.iter().rev() {
            clues.remove(idx);
        }
    }
    
    for row in &output_grid {
        for &cell in row {
            print!("{}", match cell {
                Output::Empty => '.',
                Output::Filled => '#',
                Output::Unsolved => ' ',
            });
        }
        println!();
    }
}