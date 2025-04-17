use std::cmp::Ordering;
use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

type RowCol = (i32, i32);
type Board = Vec<String>;

const DOT: char = 'o';
const H: char = '-';
const V: char = '|';
const U: char = '/';
const D: char = '\\';
const HV: char = '+';
const UD: char = 'X';
const ALL: char = '*';

fn combine(c: char, k: char) -> char {
    match (c, k) {
        (DOT, _) | (_, DOT) => DOT,
        (ALL, _) | (_, ALL) => ALL,
        (H, V) | (V, H) => HV,
        (U, D) | (D, U) => UD,
        (c, k) if (c == U || c == D || c == UD) && (k == HV || k == H || k == V) => ALL,
        (c, k) if (k == U || k == D || k == UD) && (c == HV || c == H || c == V) => ALL,
        (' ', k) => k,
        (c, ' ') => c,
        (_, k) => k,
    }
}

fn replace(board: &mut Vec<Vec<char>>, rc: &RowCol, element: char) {
    let (row, col) = *rc;
    board[row as usize][col as usize] = combine(board[row as usize][col as usize], element);
}

fn range_to(start: &RowCol, end: &RowCol) -> Vec<RowCol> {
    let (r1, c1) = *start;
    let (r2, c2) = *end;
    
    let r_sign = match (r2 - r1).cmp(&0) {
        Ordering::Greater => 1,
        Ordering::Less => -1,
        Ordering::Equal => 0,
    };
    
    let c_sign = match (c2 - c1).cmp(&0) {
        Ordering::Greater => 1,
        Ordering::Less => -1,
        Ordering::Equal => 0,
    };
    
    let mut result = vec![*start];
    let mut curr = *start;
    
    loop {
        curr = (curr.0 + r_sign, curr.1 + c_sign);
        result.push(curr);
        if curr == *end {
            break;
        }
    }
    
    result
}

fn link(board: &Board, rc1: &RowCol, rc2: &RowCol) -> Board {
    let mut tmp: Vec<Vec<char>> = board.iter().map(|s| s.chars().collect()).collect();
    let (r1, c1) = *rc1;
    let (r2, c2) = *rc2;
    
    let line = if r1 == r2 {
        H
    } else if c1 == c2 {
        V
    } else if r1 - r2 == c1 - c2 {
        D
    } else {
        U
    };
    
    for rc in range_to(rc1, rc2) {
        replace(&mut tmp, &rc, line);
    }
    
    replace(&mut tmp, rc1, DOT);
    replace(&mut tmp, rc2, DOT);
    
    tmp.iter().map(|row| row.iter().collect::<String>()).collect()
}

fn dots(board: &Board) -> Board {
    let mut positions = std::collections::HashMap::new();
    
    for (row, line) in board.iter().enumerate() {
        for (col, ch) in line.chars().enumerate() {
            if ch != '.' {
                positions.insert(ch, (row as i32, col as i32));
            }
        }
    }
    
    let order: Vec<char> = ('1'..='9').chain('A'..='Z').collect();
    let mut curr: Board = board.iter()
        .map(|line| line.replace('.', " "))
        .collect();
    
    for i in 0..order.len() - 1 {
        let a = order[i];
        let b = order[i + 1];
        
        if let (Some(pa), Some(pb)) = (positions.get(&a), positions.get(&b)) {
            curr = link(&curr, pa, pb);
        }
    }
    
    curr.iter()
        .map(|line| line.trim_end().to_string())
        .collect()
}

fn main() {

    let dimensions: Vec<i32> = parse_input!(String)
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();
    
    let mut src = Vec::new();
    for _ in 0..dimensions[0] {
        src.push(parse_input!(String));
    }
    
    let result = dots(&src);
    for line in result {
        println!("{}", line);
    }
}