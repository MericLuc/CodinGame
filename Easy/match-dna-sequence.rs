use std::io::*;

fn diff(src: &str, tgt: &str, max_delta: usize) -> usize {
    let mut d = 0; 
    if  tgt.len() < src.len() { 
        d = src.len() - tgt.len();
    }
    
    for (c1, c2) in src.chars().zip( tgt.chars() ) {
        if c1 != c2 {
            d += 1;
        }

        if d > max_delta {
            break
        }
    }

    return d;
}

fn main() {

    let stdin = stdin();
    let mut lines = stdin.lock().lines().map(Result::unwrap);

    let delta: usize = lines.next().unwrap().parse().unwrap();
    let gene = lines.next().unwrap();
    let _ = lines.next();

    let mut res: Option<(usize, usize, usize)> = None;
    
    for (i, elm) in lines.collect::<Vec<String>>().iter().enumerate() {
        eprintln!("{} : {}", i, elm);

        for (j, _) in elm.as_bytes().iter().enumerate() {
            let cur_delta = diff(&gene, &elm[j..], delta);
            if delta >= cur_delta {
                res = Some( (i, j, cur_delta) );
                break;
            }
        }
    }

    match res {
        Some(val) => println!("{} {} {}", val.0, val.1, val.2),
        None => println!("NONE"),
    }
}
