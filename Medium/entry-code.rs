use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

// https://fr.wikipedia.org/wiki/Suite_de_de_Bruijn
fn de_bruijn(k: u8, n: usize) -> String {
    let alphabet = ('0'..(k + b'0') as char).collect::<Vec<char>>();
    let mut a = vec![0; k as usize * n];
    let mut sequence = vec![];

    fn db(a: &mut [usize], sequence: &mut Vec<usize>, t: usize, p: usize, k: usize, n: usize) {
        if t > n {
            if 0 == n % p {
                sequence.extend(&a[1..p + 1]);
            }
        } else {
            a[t] = a[t - p];
            db(a, sequence, t + 1, p, k, n);
            for j in a[t - p] + 1..k {
                a[t] = j;
                db(a, sequence, t + 1, t, k, n);
            }
        }
    }

    db(&mut a, &mut sequence, 1, 1, k as usize, n);
    sequence
        .into_iter()
        .map(|i| alphabet[i])
        .collect::<String>()
}

fn main() {
    let x = parse_input!(u8);
    let n = parse_input!(usize);

    println!("{}{}", de_bruijn(x, n), (0..n - 1).map(|_| '0').collect::<String>());
}
