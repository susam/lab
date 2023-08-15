use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {
    let secret_number = rand::thread_rng().gen_range(1..=100);
    println!("The secret number is {secret_number}.");

    loop {
        let mut guess = String::new();
        println!("The variable guess has been initialized to: \"{guess}\"");

        println!("Guess the number!");
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        println!("The guessed number is [{guess}].");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        println!("You guessed {guess}.");

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
