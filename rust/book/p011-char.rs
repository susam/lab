use std::mem;

fn main() {
    let a = 'a';
    let b: char = 'b';
    let c = '♥';

    println!("a: {a}; mem::size_of_val(&a): {}", mem::size_of_val(&a));
    println!("b: {b}; mem::size_of_val(&b): {}", mem::size_of_val(&b));
    println!("c: {c}; mem::size_of_val(&c): {}", mem::size_of_val(&c));
}
