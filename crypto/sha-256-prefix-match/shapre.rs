use sha2::{Digest, Sha256};
use std::any::type_name_of_val;
use std::time::Instant;

macro_rules! cast {
    ($value: expr, $target_type: ty) => {
        <$target_type>::try_from($value).unwrap()
    };
}

fn _printt<T>(value: &T) {
    println!("{}", type_name_of_val(value));
}

fn check(candidate: String) -> bool {
    let msg = "The SHA-256 digest of this message, in hexadecimal form, begins with ".to_owned()
        + &candidate
        + ".";
    let digest = Sha256::digest(&msg);
    let result = format!("{digest:x}");
    if result.starts_with(&candidate) {
        println!("{msg}\n{result}");
        true
    } else {
        false
    }
}

fn solve(length: u8) {
    // Constraint: length in [0, 255].
    let chars: [char; 16] = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
    ];
    let base: u8 = cast!(chars.len(), u8); // Typically in [1, 32].
    let mut arrangement: Vec<u8> = vec![0; cast!(length, usize)];
    let max_count: u128 = cast!(base, u128).pow(cast!(length, u32)); // Typically <= 16^32 = 2^128.
    let mut count: u128 = 0;
    let chunk_size: u128 = 10_000_000;
    let start_time: Instant = Instant::now();
    println!("solving for length {length} with {max_count} arrangements");
    loop {
        let mut i: usize = 0;
        while i == 0 || (arrangement[i - 1] == 0 && i < cast!(length, usize)) {
            arrangement[i] = (arrangement[i] + 1) % base;
            i += 1;
        }
        if i == cast!(length, usize) && arrangement[i - 1] == 0 {
            break;
        }
        let candidate: String = arrangement
            .iter()
            .map(|&i| chars[cast!(i, usize)])
            .collect();
        count += 1;
        if count == 1 || count % chunk_size == 0 {
            let elapsed: u64 = start_time.elapsed().as_secs();
            let remaining: u64 = cast!((max_count - count) * cast!(elapsed, u128) / count, u64);
            println!(
                "[{elapsed} s of {remaining} s] checked chunk {} of {}",
                count / chunk_size,
                (max_count + chunk_size - 1) / chunk_size,
            )
        }
        if check(candidate.clone()) {
            break;
        }
    }
    println!();
}

fn main() {
    solve(1);
    solve(2);
    solve(3);
    solve(4);
    solve(5);
    solve(6);
    solve(7);
    solve(8);
}
