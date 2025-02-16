use std::io;

fn read_string() -> String {
    let mut input_line = String::new();
    io::stdin().read_line(&mut input_line).unwrap();
    input_line.trim_matches('\n').to_string()
}

fn main() {
    let length_of_line = read_string().parse::<usize>().unwrap();
    let N = read_string().parse::<usize>().unwrap();
    
    let mut line = Vec::new();
    for _ in 0..N {
        line.push(read_string());
    }
    
    let mut counter = vec![1; 20];

    for i in 0..N {
        let mut new_line = String::new();
        
        let indent_count = line[i].chars().filter(|&c| c == '>').count();
        
        for _ in 0..indent_count {
            new_line.push_str("    ");
        }

        new_line.push_str(&counter[indent_count].to_string());
        new_line.push(' ');

        for g in (indent_count + 1)..counter.len() {
            counter[g] = 1;
        }
        
        counter[indent_count] += 1;

        let parts: Vec<&str> = line[i].split(' ').collect();
        let title = parts[0].replace(">", "");
        let page = parts[1];

        new_line.push_str(&title);

        let dots_count = length_of_line - new_line.len() - page.len();
        for _ in 0..dots_count {
            new_line.push('.');
        }

        new_line.push_str(page);

        println!("{}", new_line);
    }
}