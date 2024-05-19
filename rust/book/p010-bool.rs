use std::mem;

fn main() {
    let t = true;
    let f: bool = false;

    println!("t: {t}; mem::size_of_val(&t): {}", mem::size_of_val(&t));
    println!("f: {f}; mem::size_of_val(&f): {}", mem::size_of_val(&f));
}
