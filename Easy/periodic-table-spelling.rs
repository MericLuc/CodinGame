use std::io;
use std::collections::HashSet;

fn ways(word: &str, idx: usize, current: &mut Vec<String>, out_list: &mut Vec<String>, alphabet: &HashSet<String>) {
    // Base case: reached end of string
    if idx == word.len() {
        return out_list.push(current.join("")); 
    }

    // Try taking 2 characters if possible
    if idx < word.len() - 1 {
        let two_char = &word[idx..idx + 2].to_uppercase();
        if let Some(element) = alphabet.iter()
            .find(|x| x.eq_ignore_ascii_case(two_char)) {
            current.push(element.to_string());
            ways(word, idx + 2, current, out_list, alphabet);
            current.pop();
        }
    }
    
    // Try taking 1 character
    let one_char = &word[idx..idx + 1];
    if let Some(element) = alphabet.iter()
        .find(|x| x.eq_ignore_ascii_case(one_char)) {
        current.push(element.to_string());
        ways(word, idx + 1, current, out_list, alphabet);
        current.pop();
    }

}

fn main() {
    let elements: HashSet<String> = vec![
        "H",  "He", "Li", "Be", "B",  "C",  "N",  "O",  "F",  "Ne",
        "Na", "Mg", "Al", "Si", "P",  "S",  "Cl", "Ar", "K",  "Ca",
        "Sc", "Ti", "V",  "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
        "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y",  "Zr",
        "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
        "Sb", "Te", "I",  "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
        "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
        "Lu", "Hf", "Ta", "W",  "Re", "Os", "Ir", "Pt", "Au", "Hg",
        "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
        "Pa", "U",  "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm",
        "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds",
        "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"
    ].iter().map(|&s| s.to_string()).collect();

    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();

    let word = input_line.trim_matches('\n').to_uppercase().to_string();

    let mut current = Vec::new();
    let mut output = Vec::new();
    ways(&word, 0, &mut current, &mut output, &elements);

    if output.is_empty() {
        println!("none");
    } else {
        output.sort();
        for element in output {
            println!("{}", element);
        }
    }

}
