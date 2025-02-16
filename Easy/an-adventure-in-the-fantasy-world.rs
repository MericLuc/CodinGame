use std::io;
use std::collections::HashMap;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

enum NodeType {
    Enemy(String),
    Money(u32),
}

fn main() {
    let mut infos = HashMap::new();
    let path = read_string();
    
    let mut pos = (0,0);
    let mut gold = 50;
    let mut fought: Option<String> = None;

    for _ in 0..read_string().parse::<usize>().unwrap() {
        let info = read_string();
        let parts: Vec<&str> = info.split_whitespace().collect();
        infos.insert((parts[0].parse::<i32>().unwrap(), parts[1].parse::<i32>().unwrap()),
        match parts[2] {
            "enemy" => NodeType::Enemy(parts[3].to_string()),
            _ => NodeType::Money(parts[3].replace("G", "").parse::<u32>().unwrap()),
        });
    }

    for x in path.chars() {
        match x {
            'U' => pos.0 -= 1,
            'D' => pos.0 += 1,
            'R' => pos.1 += 1,
            _ => pos.1 -= 1,
        }

        if let Some(node) = infos.get(&pos) {
            match node {
                NodeType::Enemy(name) => {
                    match name.as_str() {
                        "goblin"  => {
                            if 50 > gold {
                                fought = Some(name.to_string());
                                break;
                            } 
                            gold -= 50;
                        }
                        _ => {
                            fought = Some(name.to_string());
                            break;
                        }
                    }
                }
                NodeType::Money(val) => {
                    gold += val;
                    infos.remove(&pos);
                }
            }
        }
    }

    match fought {
        Some(enemy) => println!("{} {} {}G {}", pos.0, pos.1, gold, enemy),
        None => println!("GameClear {} {} {}G", pos.0, pos.1, gold),
    };
}
