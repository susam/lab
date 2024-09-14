use std::mem;

fn main() {
    let a = (1, 2, 3);
    let b = (1, 2u8);
    println!("a: {a:?}; mem::size_of_val(&a): {}", mem::size_of_val(&a));
    println!("b: {b:?}; mem::size_of_val(&b): {}", mem::size_of_val(&b));
    println!();

    let (c, d, e) = a;
    println!("c: {c}; mem::size_of_val(&c): {}", mem::size_of_val(&c));
    println!("d: {d}; mem::size_of_val(&d): {}", mem::size_of_val(&d));
    println!("e: {e}; mem::size_of_val(&e): {}", mem::size_of_val(&e));
    println!();

    let (f, g) = b;
    println!("f: {f}; mem::size_of_val(&f): {}", mem::size_of_val(&f));
    println!("f: {g}; mem::size_of_val(&g): {}", mem::size_of_val(&g));
}
