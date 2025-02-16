use std::collections::HashSet;
use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {

    fn cards(description: &str) -> HashSet<String> {

        let all_ranks: HashSet<char> = "23456789TJQKA".chars().collect();
        let all_suits: HashSet<char> = "CDHS".chars().collect();

        let chars: HashSet<char> = description.chars().collect();
        let ranks: HashSet<char> = chars.iter().cloned().filter(|c| all_ranks.contains(c)).collect();
        let suits: HashSet<char> = chars.iter().cloned().filter(|c| all_suits.contains(c)).collect();

        let ranks_to_use = if ranks.is_empty() { &all_ranks } else { &ranks };
        let suits_to_use = if suits.is_empty() { &all_suits } else { &suits };

        let mut result = HashSet::new();
        for &r in ranks_to_use {
            for &s in suits_to_use {
                result.insert(format!("{}{}", r, s));
            }
        }
        result
    }

    let mut deck: HashSet<String> = cards("");
    let mut want: HashSet<String> = HashSet::new();

    let inputs = read_string();
    let inputs = inputs.split(" ").collect::<Vec<_>>();
    let (r, s) = (inputs[0].parse::<usize>().unwrap(), inputs[1].parse::<usize>().unwrap() );
    
    for _ in 0..r {
        let description = read_string();
        let removed_cards = cards(&description);
        deck = deck.difference(&removed_cards).cloned().collect();
    }

    for _ in 0..s {
        let description = read_string();
        let wanted_cards = cards(&description);
        want.extend(wanted_cards);
    }

    let intersection: HashSet<_> = want.intersection(&deck).collect();
    let odds = (intersection.len() as f64) / (deck.len() as f64);
    let percentage = (odds * 100.0).round() as i32;
    
    println!("{}%", percentage);
}