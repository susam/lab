use std::mem;

fn main() {
    let x = 2.0;
    let y: f32 = 3.0;
    let z = 4.0f32;
    println!("x: {x}; mem::size_of_val(&x): {}", mem::size_of_val(&x));
    println!("y: {y}; mem::size_of_val(&y): {}", mem::size_of_val(&y));
    println!("z: {z}; mem::size_of_val(&z): {}", mem::size_of_val(&z));
    println!();

    println!("10 / 3: {}", 10 / 3);
    println!("10.0 as i32 / 3: {}", 10.0 as i32 / 3);
    println!("10.0 / 3.0: {}", 10.0 / 3.0);

    // no implementation for `{float} / {integer}`
    // println!("{}", 10.0 / 3);

    // no implementation for `{integer} / {float}`
    // println!("{}", 10 / 3.0);
}
