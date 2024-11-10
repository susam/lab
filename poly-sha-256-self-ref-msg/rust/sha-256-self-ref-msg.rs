use sha2::{Digest, Sha256};
use std::time::Instant;

macro_rules! cast {
    ($value: expr, $target_type: ty) => {
        <$target_type>::try_from($value).unwrap()
    };
}

fn check(candidate: String) {
    let msg = "The SHA-256 hash of this text begins with ".to_owned() + &candidate + ".";
    let digest = Sha256::digest(&msg);
    let result = format!("{digest:x}");
    if result.starts_with(&candidate) {
        println!("{msg}\n{result}");
    }
}

fn solve(length: u8) {
    // Let length <= 32.
    let chars: [char; 16] = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
    ];
    let base: u8 = cast!(chars.len(), u8); // Let base <= 16.
    let mut arrangement: Vec<u8> = vec![0; cast!(length, usize)];
    let max_count: u128 = cast!(base, u128).pow(cast!(length, u32)); // Then max_count <= 16^32 = 2^128.
    let mut count: u128 = 0;
    let chunk_size: u128 = 10_000_000;
    let start_time: Instant = Instant::now();
    println!("solving for length {length} with {max_count} arrangements");
    loop {
        // Generate candidate message.
        let candidate: String = arrangement
            .iter()
            .map(|&i| chars[cast!(i, usize)])
            .collect();

        // Check if the candidate string is a solution.
        check(candidate.clone());

        // Compute the next arrangement for generating the next candidate.
        let mut i: usize = 0;
        while i == 0 || (arrangement[i - 1] == 0 && i < cast!(length, usize)) {
            arrangement[i] = (arrangement[i] + 1) % base;
            i += 1;
        }

        // Log progress after every chunk_size iterations.
        count += 1;
        if count % chunk_size == 0 || count == max_count {
            let elapsed: u64 = start_time.elapsed().as_secs();
            let remaining: u64 = cast!((max_count - count) * cast!(elapsed, u128) / count, u64);
            println!(
                "[{elapsed} s of {remaining} s] checked chunk {} of {}",
                (count + chunk_size - 1) / chunk_size,
                (max_count + chunk_size - 1) / chunk_size,
            );
        }

        // Quit if there are no more arrangements to check.
        if i == cast!(length, usize) && arrangement[i - 1] == 0 {
            break;
        }
    }
    println!();
}

fn main() {
    solve(7);
}
