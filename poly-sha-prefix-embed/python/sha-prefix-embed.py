import hashlib
import itertools
import time


def solve(length: int):
    chars: str = "0123456789abcdef"
    base: int = len(chars)
    max_count: int = base**length
    count = 0
    chunk_size: int = 10_000_000
    start_time: float = time.time()
    print(f"solving for length {length} with {max_count} arrangements")
    for arrangement in itertools.product(chars, repeat=length):
        # Generate candidate message.
        candidate: str = "".join(arrangement)
        msg: str = "The SHA-256 hash of this sentence begins with " + candidate + "."

        # Check if the candidate string is a solution.
        result: str = hashlib.sha256(msg.encode()).hexdigest()
        if result.startswith(candidate):
            print(f"\n{msg}\n{result}\n")

        # Log progress after every chunk_size iterations.
        count += 1
        if count % chunk_size == 0 or count == max_count:
            elapsed: int = int(time.time() - start_time)
            remaining: int = (max_count - count) * elapsed // count
            print(
                f"[{elapsed} s of {remaining} s] checked chunk "
                f"{(count + chunk_size - 1) // chunk_size} of "
                f"{(max_count + chunk_size - 1) // chunk_size} ({candidate})"
            )


if __name__ == "__main__":
    solve(7)
