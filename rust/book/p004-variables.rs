// let a = 20;
// ^^^ consider using `const` or `static` instead of `let` for global variables

fn main() {
    let x = 5;
    println!("x = {x}");

    // x = 6;
    // ^^^^^ cannot assign twice to immutable variable

    let mut y = 5;
    println!("y = {y}");
    y = 6;
    println!("y = {y}");
}
