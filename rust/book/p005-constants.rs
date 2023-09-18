const A: u32 = 10;

// warning: constant `B` is never used
const B: u32 = 20;

fn main() {
    const B: u32 = 30;
    const C: u32 = 40;
    println!("A: {A}");
    println!("B: {B}");
    println!("C: {C}");
}
