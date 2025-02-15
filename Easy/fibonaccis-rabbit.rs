use std::io;

fn read_line() -> (usize,usize) {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    let inputs = input_line.trim_matches('\n').split(" ").collect::<Vec<_>>();
    (inputs[0].parse::<usize>().unwrap(), inputs[1].parse::<usize>().unwrap())
}

fn main() {

    let (f0, n) = read_line();
    let (a, b) = read_line();
    
    let mut f: Vec::<u64> = vec![0; b];
    f.push(f0 as u64);

    for _ in 1..=n as usize {
        for prev in 0..b as usize {
            f[prev] = f[prev+1];
        }
        f[b] = f[..=(b-a)].iter().sum();
    }
    println!("{}", f[b]);
}
