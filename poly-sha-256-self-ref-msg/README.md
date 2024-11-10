Polyglot SHA-256 Search for Self-Referential Message
====================================================

The experiments in this directory implement searching for messages
that describe their own SHA-256 digests in various programming
languages.  The running time of each program is noted in the table
below.


Result Set
----------

The results presented in this section were obtained on a MacBook Pro
16-inch, 2021 system with Apple M1 Pro chip, 16 GB memory, and macOS
Sequoia 15.0.1.  Here are some additional details:

```
$ sysctl hw.ncpu hw.memsize
hw.ncpu: 10
hw.memsize: 17179869184

$ go version
go version go1.23.2 darwin/arm64

$ python3 --version
Python 3.13.0

$ rustc --version
rustc 1.82.0 (f6e511eec 2024-10-15)
```

The output from the `time` command is noted in the tables below.  For
each program, five trials were performed and the results from the five
trials have been arranged in the ascending order of `real` time.


### Averages

| Language |   real |   user |  sys |
|----------|-------:|-------:|-----:|
| Go       |  84.58 |  85.23 | 1.28 |
| Python   | 153.09 | 152.86 | 0.22 |
| Rust     |  89.22 |  88.81 | 0.14 |


### Go Results

| Trial |  real |  user |  sys |
|------:|------:|------:|-----:|
|     1 | 84.44 | 85.11 | 1.27 |
|     2 | 84.49 | 85.12 | 1.30 |
|     3 | 84.63 | 85.28 | 1.28 |
|     4 | 84.65 | 85.29 | 1.31 |
|     5 | 84.69 | 85.35 | 1.24 |


### Python Results

| Trial |   real |   user |  sys |
|------:|-------:|-------:|-----:|
|     1 | 152.02 | 151.80 | 0.21 |
|     2 | 152.59 | 152.33 | 0.25 |
|     3 | 153.38 | 153.16 | 0.22 |
|     4 | 153.46 | 153.24 | 0.21 |
|     5 | 153.99 | 153.77 | 0.22 |


### Rust Results

| Trial |  real |  user |  sys |
|------:|------:|------:|-----:|
|     1 | 88.94 | 88.58 | 0.14 |
|     2 | 88.99 | 88.61 | 0.14 |
|     3 | 89.00 | 88.55 | 0.14 |
|     4 | 89.72 | 89.24 | 0.15 |
|     5 | 89.45 | 89.08 | 0.15 |
