use std::{io, cmp::Reverse, collections::{HashMap, HashSet, BinaryHeap}};

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn parse_import() -> String {
    let input = read_string();
    let v: Vec<&str> = input.split_whitespace().collect();

    v[1].to_string()
}

fn parse_dep(deps : &mut HashMap<String, Vec<String>>) {
    let input = read_string();

    if let Some(pos) = input.find("requires") {
        let deps_str = &input[pos + "requires".len()..].trim();

        deps.insert(input.split_whitespace().next().unwrap().to_string(), 
                       deps_str.split(',')
                            .map(|s| s.trim().to_string())
                            .collect()
        );
    }
}

fn main() {
    let mut deps: HashMap<String, Vec<String>> = HashMap::new();
    let mut imports: HashSet<String> = HashSet::new();
    let mut todo: Vec<String> = Vec::new();
    let mut err = false;

    for _ in 0..read_string().parse::<usize>().unwrap() {
        let lib = parse_import();
        deps.insert(lib.to_string(), Vec::new());
        todo.push(lib);
    }

    for _ in 0..read_string().parse::<usize>().unwrap() {
        parse_dep(&mut deps);
    }

    for import in &todo {
        if let Some(deps) = deps.get(import) {
            for dep in deps {
                if !imports.contains(dep) {
                    println!("Import error: tried to import {} but {} is required.", import, dep);
                    err = true;
                    break;
                } 
            }
        }
        if err {
            break;
        }
        imports.insert(import.to_string());
    }

    if !err {
        println!("Compiled successfully!");
    } else {
        let mut h = BinaryHeap::new();
    
        for (lib, dep) in &deps {
            if dep.is_empty() {
                h.push(Reverse(lib.clone()));
            }
        }
    
        let mut record = Vec::new();
    
        while let Some(Reverse(lib)) = h.pop() {
            record.push(lib.clone());
    
            for dep in deps.values_mut() {
                if let Some(pos) = dep.iter().position(|x| *x == lib) {
                    dep.remove(pos);
                }
            }
    
            for (lib, dep) in &deps {
                if dep.is_empty() && !record.contains(&lib) && !h.iter().any(|x| x.0 == *lib) {
                    h.push(Reverse(lib.clone()));
                }
            }
        }
    
        if record.len() != deps.len() {
            println!("Fatal error: interdependencies.");
        } else {
            println!("Suggest to change import order:");
            for library in record {
                println!("import {}", library);
            }
        }
    }
}
