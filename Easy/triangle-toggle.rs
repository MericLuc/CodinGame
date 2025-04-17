use std::{fmt, io};

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

#[derive(Debug, Clone, PartialEq)]
enum Style {
    Expanded,
    Condensated,
}

struct Point {
    x: i32,
    y: i32,
}

struct Triangle {
    a: Point, 
    b: Point, 
    c: Point,
}

struct Grid {
    height: usize,
    width: usize,
    style: Style,
    data: Vec<Vec<char>>,
}

impl Point {
    fn new(x: i32, y: i32) -> Self {
        Self{ x, y }
    }
}

impl Triangle {
    fn new(input: &str) -> Self {
        let p = input
            .split_whitespace()
            .map(|x| x.parse::<i32>().unwrap())
            .collect::<Vec<_>>();

            Self{   a: Point::new(p[1], p[0]), 
                    b: Point::new(p[3], p[2]), 
                    c: Point::new(p[5], p[4]) }
    }

    fn contains(&self, pt: &Point) -> bool {
        let d1 = self.sign(&pt, &self.a, &self.b);
        let d2 = self.sign(&pt, &self.b, &self.c);
        let d3 = self.sign(&pt, &self.c, &self.a);

        (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0)
    }

    fn sign(&self, p1: &Point, p2: &Point, p3: &Point) -> i32 {
        (p1.y - p3.y) * (p2.x - p3.x) - (p2.y - p3.y) * (p1.x - p3.x)
    }
}

impl Grid {
    fn new(height: usize, width: usize, style: Style) -> Self {
        Self{ height, width, style, data: vec![vec!['*'; width]; height] }
    }

    fn carve(&mut self, triangle: &Triangle) {
        for x in 0..self.height as i32 {
            for y in 0..self.width as i32 { 
                let pt = Point::new(x, y);
                if triangle.contains(&pt) {
                    self.toggle(&pt);
                }
            }
        }
    }
    
    fn toggle(&mut self, pt: &Point) {
        let (x, y) = (pt.x as usize, pt.y as usize);
        self.data[x][y] = match self.data[x][y] {
            '*' => ' ',
            _ => '*',
        }
    }
}

impl fmt::Display for Grid {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for (i, row) in self.data.iter().enumerate() {

            write!(f, "{}", row[0])?;
            for &cell in &row[1..] {
                if Style::Expanded == self.style {
                    write!(f, " ")?;
                }
                write!(f, "{}", cell)?;
            }
            
            if i < self.data.len() - 1 {
                writeln!(f)?;
            }
        }
        Ok(())
    }
}

fn main() {
    let inputs = parse_input!(String)
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap()).collect::<Vec<_>>();

    let mut grid = Grid::new(
        inputs[0], 
        inputs[1], 
        match parse_input!(String).as_str() {
        "expanded" => Style::Expanded,
        _ => Style::Condensated,
    });

    for _ in 0..parse_input!(u32) {
        grid.carve(&Triangle::new(&parse_input!(String)));
    }

    println!("{grid}");
}
