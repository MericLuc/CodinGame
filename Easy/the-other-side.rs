use std::io;
use std::collections::HashSet;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {
    let h = read_string().parse::<usize>().unwrap();
    let w = read_string().parse::<usize>().unwrap();
    let mut graph = Vec::new();
    let mut count = 0;

    for _ in 0..h as usize {
        graph.push(read_string().replace(" ", "").chars().map(|x| match x {
            '+' => true,
            _   => false,
        }).collect::<Vec<bool>>());
    }

    for i in 0..graph.len() {
        if !graph[i][0] {
            continue;
        }

        let mut visited = HashSet::new();
        let mut stack = Vec::new();
        stack.push((i, 0usize));

        while let Some((x, y)) = stack.pop() {
            if visited.contains(&(x, y)) {
                continue;
            }

            if w-1 == y {
                count += 1;
                stack.clear();
                continue;
            }

            if 0   != y && graph[x  ][y-1] { stack.push((x, y-1)); }
            if w-1 != y && graph[x  ][y+1] { stack.push((x, y+1)); }
            if 0   != x && graph[x-1][y  ] { stack.push((x-1, y)); }
            if h-1 != x && graph[x+1][y  ] { stack.push((x+1, y)); }

            visited.insert((x, y));
        }
    }

    println!("{}", count);
}
