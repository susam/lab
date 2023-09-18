fn main() {
    let x = 10;
    println!("x: {x}");

    let x = x * 2;
    println!("x: {x}");

    let x = "hello";
    println!("x: {x}");

    {
        let x = x.len();
        println!("x: {x}");
    }

    println!("x: {x}");

    // x = 30;
    //     ^^ expected `&str`, found integer
}
