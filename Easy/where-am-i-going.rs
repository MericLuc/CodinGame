use std::io;

macro_rules! parse_input {
    ($x:expr, $t:ident) => ($x.trim().parse::<$t>().unwrap())
}

fn read_int() -> i32 {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    parse_input!(input_line, i32)
}

fn read_str() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    input_line.trim_matches('\n').to_string()
}

struct Pos {
    x: i32,
    y: i32
}

impl Pos {
    fn move_dir(&mut self, dir: &Pos) {
        self.x += dir.x;
        self.y += dir.y;
    }

    fn copy(&self) -> Pos {
        Pos { x:self.x, y: self.y }
    }
}

fn advance(pos: &mut Pos, dir: &Pos, grid: &mut Vec<Vec<char>>) -> bool {
    let mut tmp_pos = pos.copy();
    tmp_pos.move_dir(dir);

    if '#' == grid[tmp_pos.x as usize][tmp_pos.y as usize] {
        grid[tmp_pos.x as usize][tmp_pos.y as usize] = '.';
        *pos = tmp_pos.copy();
        return true
    }
    false
}

fn get_diff(heading: &i32) -> Pos {
    match heading {
        0 => Pos{ x: -1, y: 0}, // North
        1 => Pos{ x: 0, y: 1},  // East
        2 => Pos{ x: 1, y: 0},  // South
        _ => Pos{ x: 0, y: -1}  // West
    }
}

fn determine_turn(heading: &mut i32, pos: &mut Pos, grid: &mut Vec<Vec<char>>) -> char {
    let heading_next = (*heading + 1) % 4;

    if advance(pos, &get_diff(&heading_next), grid) {
        *heading = heading_next;
        return 'R'
    } 

    let heading_next = (*heading + 3) % 4;
    if advance(pos, &get_diff(&heading_next), grid) {
        *heading = heading_next;
        return 'L'
    }

    'U'
}

fn main() {
    let h = read_int();
    let w = read_int();

    let mut grid = Vec::<Vec<char>>::new();
    grid.push(vec!['.'; (w + 2) as usize]);
    for _ in 0..h {
        let mut row: Vec<char> = vec!['.'];
        row.extend(read_str().chars());
        row.push('.');
        grid.push(row);
    }
    grid.push(vec!['.'; (w + 2) as usize]);

    let mut heading = 1;
    let mut pos = Pos{ x: 1, y: 0 };
    let mut dir = get_diff(&heading);
    let mut repeat = 0;

    loop {

        while advance(&mut pos, &dir, &mut grid) {
            repeat+=1;
        }

        print!("{}", repeat);

        let turn = determine_turn(&mut heading, &mut pos, &mut grid);
        if 'U' == turn {
            break;
        }

        print!("{}", turn);
        repeat = 1;
        dir = get_diff(&heading);
    }
}
