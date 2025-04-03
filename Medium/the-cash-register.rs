use std::io;

macro_rules! parse_input {
    ($t:ident) => {{
        let mut input_line = String::new();
        io::stdin().read_line(&mut input_line).unwrap();
        input_line.trim_matches('\n').parse::<$t>().unwrap()
    }}
}

fn perform(register: &[i32], goal: i32) -> Result<Vec<i32>, &'static str> {
    if goal == 0 {
        return Ok(vec![0]);
    } 
    if register.contains(&goal) {
        return Ok(vec![goal]);
    }

    let mut open: Vec<Vec<i32>> = register.iter().map(|&coin| vec![coin]).collect();
    let mut amounts: Vec<i32> = Vec::new();

    loop {
        let mut cur: Vec<Vec<i32>> = Vec::new();
        for poss in open {
            for &coin in register {
                let mut new_poss = poss.clone();
                new_poss.push(coin);
                let rendu =new_poss.iter().sum();
                if rendu == goal {
                    return Ok(new_poss);
                } 
                if rendu < goal && !amounts.contains(&rendu) {
                    cur.push(new_poss);
                    amounts.push(rendu);
                }
            }
        }
        if cur.is_empty() {
            return Err("IMPOSSIBLE");
        }
        open = cur;
    }
}

fn main() {
    let register: Vec<i32> = parse_input!(String)
        .trim()
        .split(' ')
        .map(|s| s.parse().unwrap_or(0))
        .collect();
    let goal_amount: i32 = parse_input!(i32);

    match perform(&register, goal_amount) {
        Ok(res) => { 
            println!("{}",
            if let Some((last, elements)) = res.split_last() {
                std::iter::once(last)
                    .chain(elements.iter().rev())
                    .map(|x| x.to_string())
                    .collect::<Vec<_>>()
                    .join(" ")
            } else {
                "".to_string()
            });
        }
        Err(e) => println!("{}", e),
    }
}
