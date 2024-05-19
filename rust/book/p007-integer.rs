use std::mem;

fn main() {
    let a: u8 = 254;

    // thread 'main' panicked at 'attempt to add with overflow'
    // let b = a + 5;

    let b = a.wrapping_add(5);
    println!("a: {a}; b: {b}");

    let c = a.saturating_add(5);
    println!("c: {c}");

    let d = match a.checked_add(5) {
        Some(v) => v,
        None => 101,
    };
    println!("d: {d}");

    let e = match a.checked_add(1) {
        Some(v) => v,
        None => 101,
    };
    println!("e: {e}");
    println!();

    let f: u8 = 20;
    let g = 30u8;
    println!("f: {f}; mem::size_of_val(&f): {}", mem::size_of_val(&f));
    println!("g: {g}; mem::size_of_val(&g): {}", mem::size_of_val(&f));
    println!();

    let h = 10;
    let i = 10i16;
    println!("h: {h}; mem::size_of_val(&h): {}", mem::size_of_val(&h));
    println!("i: {i}; mem::size_of_val(&i): {}", mem::size_of_val(&i));
    println!("mem::size_of_val(&10): {}", mem::size_of_val(&10));
    println!("mem::size_of_val(&10u64): {}", mem::size_of_val(&10u64));
    println!();

    let l = "hello".len();
    println!("l: {l}; mem::size_of_val(&l): {}", mem::size_of_val(&l));
    println!(
        "mem::size_of_val(&\"hello\".len()): {}",
        mem::size_of_val(&"hello".len()),
    );
    println!();

    println!(
        "mem::size_of_val(&mem::size_of_val(&10)): {}",
        mem::size_of_val(&mem::size_of_val(&10)),
    );
}
