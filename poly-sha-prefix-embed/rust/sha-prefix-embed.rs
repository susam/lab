use sha2::{Digest, Sha256};
use std::time::Instant;

macro_rules! cast {
    ($value: expr, $target_type: ty) => {
        <$target_type>::try_from($value).unwrap()
    };
}

fn check(candidate: &String) {
    let msg = "The SHA-256 hash of this sentence begins with ".to_owned() + candidate + ".";
    let digest = Sha256::digest(&msg);
    let result = format!("{digest:x}");
    if result.starts_with(candidate) {
        println!("\n{msg}\n{result}\n");
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
    let log_interval: u128 = 10_000_000;
    let start_time: Instant = Instant::now();

    println!("solving for length {length} with {max_count} arrangements");
    loop {
        // Generate candidate message.
        let candidate: String = arrangement
            .iter()
            .map(|&i| chars[cast!(i, usize)])
            .collect();

        // Check if the candidate string is a solution.
        check(&candidate);

        // Log progress after every log_interval iterations.
        count += 1;
        if count % log_interval == 0 || count == max_count {
            let elapsed: u64 = start_time.elapsed().as_secs();
            let remaining: u64 = cast!((max_count - count) * cast!(elapsed, u128) / count, u64);
            println!(
                "[{elapsed} s of {remaining} s] checked chunk {} of {} ({candidate})",
                (count + log_interval - 1) / log_interval,
                (max_count + log_interval - 1) / log_interval,
            );
        }

        // Compute the next arrangement for generating the next candidate.
        let mut i: usize = cast!(length, usize); // Index of last cell incremented.
        while i == cast!(length, usize) || (arrangement[i] == 0 && i > 0) {
            i -= 1;
            arrangement[i] = (arrangement[i] + 1) % base;
        }

        // Quit if there are no more arrangements to check.
        if i == 0 && arrangement[0] == 0 {
            break;
        }
    }
}

fn main() {
    solve(7);
}
