use std::io;

const N: usize = 4;
const N_2: usize = N * N;
const POSS: u32 = (1 << N_2) - 1;
const BASE: u8 = b'A';
const VIDE: u8 = b'.';

macro_rules! bx {
    ($j:expr, $k:expr) => {
        ((($j) / N) * N + ($k) / N)
    };
}

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn backtrack(
    pos: &mut Vec<usize>,
    candrow: &mut [u32; N_2],
    candcol: &mut [u32; N_2],
    candbox: &mut [u32; N_2],
    solution: &mut [[u8; N_2]; N_2],
) -> bool {
    if pos.is_empty() {
        return true;
    }
    let mut mini = 2 * N_2;
    let mut best_idx = 0;
    for (idx, &p) in pos.iter().enumerate() {
        let i = p / N_2;
        let j = p % N_2;
        let b = bx!(i, j);
        let candidates = candrow[i] & candcol[j] & candbox[b];
        let nb = candidates.count_ones() as usize;
        if nb < mini {
            mini = nb;
            best_idx = idx;
        }
    }

    let p = pos.remove(best_idx);
    let i = p / N_2;
    let j = p % N_2;
    let b = bx!(i, j);
    let mut bitset = candrow[i] & candcol[j] & candbox[b];
    
    while bitset != 0 {
        let k = bitset.trailing_zeros();
        bitset &= !(1 << k);

        candrow[i] &= !(1 << k);
        candcol[j] &= !(1 << k);
        candbox[b] &= !(1 << k);

        if backtrack(pos, candrow, candcol, candbox, solution) {
            solution[i][j] = BASE + k as u8;
            return true;
        }

        candrow[i] |= 1 << k;
        candcol[j] |= 1 << k;
        candbox[b] |= 1 << k;
    }
    
    pos.insert(0, p);
    false
}

fn display(grid: &[[u8; N_2]; N_2]) {
    for i in 0..N_2 {
        let line: String = grid[i].iter().map(|&c| c as char).collect();
        println!("{}", line);
    }
}

fn main() {
    let mut row = [POSS; N_2];
    let mut col = [POSS; N_2];
    let mut bx = [POSS; N_2];
    let mut grid = [[0u8; N_2]; N_2];
    let mut res = [[0u8; N_2]; N_2];
    let mut pos = Vec::new();


    for l in 0..N_2 {
        for (j, &ch) in parse_input!(String).as_bytes().iter().take(N_2).enumerate() {
            grid[l][j] = ch;
        }
    }

    for i in 0..N_2 {
        for j in 0..N_2 {
            let b = bx!(i, j);
            let val = grid[i][j];
            if val != VIDE {
                let k = (val - BASE) as u32;
                row[i] &= !(1 << k);
                col[j] &= !(1 << k);
                bx[b] &= !(1 << k);
                res[i][j] = val;
            } else {
                pos.push(i * N_2 + j);
            }
        }
    }

    if backtrack(&mut pos, &mut row, &mut col, &mut bx, &mut res) {
        display(&res);
    }
}
