use std::io;
use itertools::Itertools;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn main() {
    let measures = parse_input!(String)
        .split(' ')
        .map(|x| x.parse::<i16>().unwrap_or(0))
        .collect::<Vec<_>>();
    let total_sum = measures.iter().sum::<i16>() / 4;
    
    for m in measures.iter().combinations(3) {    
        let pa = (m[0] + m[1] - m[2]) / 2;
        let pb = (m[0] + m[2] - m[1]) / 2;
        let pc = (m[1] + m[2] - m[0]) / 2;
                
        if 0 >= pa || 0 >= pb || 0 >= pc {
            continue;
        }
                
        for m in &measures {
            let pd = *m - pa;
            let pe = total_sum - (pa + pb + pc) - pd;
                    
            if 0 >= pd || 0 >= pe {
                continue;
            }
                    
            let mut expected = vec![
                pa + pb, pa + pc, pa + pd, pa + pe, pb + pc,
                pb + pd, pb + pe, pc + pd, pc + pe, pd + pe,
            ];
            expected.sort();

            if expected == measures {
                println!("{} {} {} {} {}", 
                    pa, pb, pc, pd, pe);
                return;
            }
        }
    }
}
