use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read input");
    
    let cols: Vec<&str> = input.trim().split(' ').collect();
    
    let which_direction = cols[0];
    let how_many_arrows = cols[1].parse::<i32>().unwrap();
    let height_of_arrow = cols[2].parse::<i32>().unwrap();
    let stroke_width_of_arrow = cols[3].parse::<i32>().unwrap();
    let spacing_between_arrows = cols[4].parse::<i32>().unwrap();
    let additional_indent_of_each_line = cols[5].parse::<i32>().unwrap();
    
    let half_height = 1 + (height_of_arrow / 2);
    
    let directions = "right > left <";
    let directions_arr: Vec<&str> = directions.split(' ').collect();
    let index_of_this = directions_arr.iter().position(|&r| r == which_direction).unwrap();
    let the_symbol = directions_arr[index_of_this + 1].chars().next().unwrap();
    
    let str_a = the_symbol.to_string().repeat(stroke_width_of_arrow as usize);
    let str_b = " ".repeat(spacing_between_arrows as usize);
    let str_ab = str_a + &str_b;
    
    let mut str_c = String::new();
    for _ in 0..how_many_arrows {
        str_c += &str_ab;
    }
    
    if which_direction == "right" {
        for which_row in 1..half_height {
            let indent_level = which_row - 1;
            print_row(indent_level, &str_c, additional_indent_of_each_line);
        }
        for which_row in half_height..=height_of_arrow {
            let indent_level = height_of_arrow - which_row;
            print_row(indent_level, &str_c, additional_indent_of_each_line);
        }
    }
    
    if which_direction == "left" {
        let str_c = str_c.replace('>', "<");
        for which_row in 1..half_height {
            let indent_level = half_height - which_row;
            print_row(indent_level, &str_c, additional_indent_of_each_line);
        }
        for which_row in half_height..=height_of_arrow {
            let indent_level = which_row - half_height;
            print_row(indent_level, &str_c, additional_indent_of_each_line);
        }
    }
}

fn print_row(indent_level: i32, str: &str, each_rise: i32) {
    let indent_amount = indent_level * each_rise;
    let blanks_at_beginning_of_row = " ".repeat(indent_amount as usize);
    let mut this_row = blanks_at_beginning_of_row + str;
    this_row = this_row.trim_end().to_string();
    println!("{}", this_row);
}