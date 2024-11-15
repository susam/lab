Polyglot SHA-256 Search for Self-Referential Message
====================================================

The experiments in this directory implement searching for messages
that describe their own SHA-256 digests in various programming
languages.  The running time of each program is noted in the table
below.

**Caution:** The results presented here should not be regarded as
rigorous performance benchmarks.  Proper benchmarking demands a
controlled environment, similar to the setup described in [The
Computer Language Benchmarks Game][].  No such level of sophistication
has been applied here.  The results presented here merely consist of
the outputs obtained from the Unix `time` command.  These results were
gathered solely out of curiosity and for the purpose of recording the
running time of each program on my personal device.

[TCLBG]: https://benchmarksgame-team.pages.debian.net/benchmarksgame/how-programs-are-measured.html


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
| Go       |  86.03 |  86.72 | 1.24 |
| Python   | 143.02 | 142.81 | 0.20 |
| Rust     |  84.54 |  84.17 | 0.16 |


### Go Results

| Trial |  real |  user |  sys |
|------:|------:|------:|-----:|
|     1 | 85.96 | 86.65 | 1.25 |
|     2 | 86.00 | 86.69 | 1.24 |
|     3 | 86.03 | 86.72 | 1.22 |
|     4 | 86.07 | 86.72 | 1.23 |
|     5 | 86.09 | 86.80 | 1.25 |


### Python Results

| Trial |   real |   user |  sys |
|------:|-------:|-------:|-----:|
|     1 | 141.61 | 141.41 | 0.20 |
|     2 | 142.21 | 142.01 | 0.20 |
|     3 | 143.29 | 143.08 | 0.20 |
|     4 | 143.70 | 143.49 | 0.20 |
|     5 | 144.27 | 144.06 | 0.20 |


### Rust Results

| Trial |  real |  user |  sys |
|------:|------:|------:|-----:|
|     1 | 84.47 | 84.10 | 0.15 |
|     2 | 84.48 | 84.12 | 0.15 |
|     3 | 84.56 | 84.20 | 0.15 |
|     4 | 84.56 | 84.20 | 0.15 |
|     5 | 84.63 | 84.21 | 0.18 |
