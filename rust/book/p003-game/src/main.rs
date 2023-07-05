use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {
    let mut guess = String::new();
    println!("The variable guess has been initialized to: \"{guess}\"");

    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("The secret number is: {secret_number}");

    println!("Guess the number!");
    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");
    let guess_str: u32 = guess.trim().parse().expect("Please type a number");

    println!("You guessed: {guess}");

    match guess_str.cmp(&secret_number) {
        Ordering::Less => println!("Too small!"),
        Ordering::Greater => println!("Too big!"),
        Ordering::Equal => println!("You win!"),
    }
}
