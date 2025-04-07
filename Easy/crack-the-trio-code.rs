use std::io;
use itertools::iproduct;
use std::collections::HashSet;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn is_triad_sum(cdt: i32, triad: &[i32; 3]) -> bool {
    let [a, b, c] = *triad;
    [a, b, c,
     a+a, a+b, a+c, b+b, b+c, c+c,
     a+a+a, a+a+b, a+a+c, a+b+b, a+b+c, a+c+c, b+b+b, b+b+c, b+c+c, c+c+c].contains(&cdt)
}

fn get_canonical_triad(triad: [i32; 3]) -> [i32; 3] {
    let mut sorted = triad;
    sorted.sort();
    sorted
}

fn main() {
    let input: Vec<i32> = parse_input!(String)
            .split(',')
            .map(|x| x.parse::<i32>().unwrap_or(0))
            .collect();
    let max = input.last().unwrap_or(&0);

    let mut res: HashSet<Vec<i32>> = HashSet::new();
    iproduct!(0..=*max, 0..=*max, 0..=*max)
        .filter(|&(i, j, k)| {
            let triad = [i, j, k];
            input.iter().all(|&cdt| is_triad_sum(cdt, &triad))
        })
        .for_each(|(i, j, k)| {
            let canonical = get_canonical_triad([i, j, k]);
            res.insert(canonical.to_vec());
        });


    match res.len() {
        0 => println!("none"),
        1 => {
            let triad = res.iter().next().unwrap();
            println!("{},{},{}", triad[0], triad[1], triad[2]);
        }
        _ => println!("many"),
    }
}
