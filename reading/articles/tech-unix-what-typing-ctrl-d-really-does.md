What typing ^D really does on Unix
==================================
2009-09-06: Chris Siebenmann:
https://utcc.utoronto.ca/~cks/space/blog/unix/TypingEOFEffects

Snippets
------
Typing ^D causes the tty driver to immediately finish a `read()`.

---

Normally doing a `read()` from a terminal is line-buffered inside the
tty driver; your program only wakes up when the tty driver sees the
newline, at which point you get back the full line.

---

Typing ^D causes the tty driver to stop waiting for a newline and
immediately return from the `read()` with however much of the line has
been accumulated to date. If you haven't typed anything on the line yet,
there is nothing accumulated and the `read()` will return 0 bytes, which
is conveniently the signal for end of file.

---

Once you've typed ^D on a partial line, that portion of the line is
immutable because it's already been given to the program. Most Unixes
won't let you backspace over such partial lines; effectively they become
output, not input.

---

Note that modern shells are not good examples of this, because they
don't do line-buffered input; to support command line editing, they
switch terminal input into an uninterpreted mode. So they get the raw ^D
and can do whatever they want with it, and they can let you edit as much
of the pending line as they want.

Notes
-----
- As a corollary, typing ^D twice on a non-empty line will also send EOF
  on the input, allowing you to provide a program with input not ending
  with \n from the command line. I knew about this behavior, but not why
  it worked, but this article's explanation clarifies this behavior as
  well. The first ^D terminates the read() call, passing the line so
  far, without terminating \n, to the program. The second causes read()
  to return with 0 read bytes, which is EOF, as explained in the
  article. -- telotortium ([HN][])
- Actually bash (by default) does do something special with ^D: it's
  mapped to the "delete-the-char-after-the-cursor" functionality (just
  like the DEL key is), by analog to the delete-char binding in emacs.
  But indeed, it's in raw mode so the kernel doesn't do anything special
  and just emits the 0x04 byte down the descriptor. -- ajross ([HN][])
- In particular, on Linux, you can experiment in dash. You'll find that
  the behavior is exactly the same as this article, since the terminal
  remains in cooked mode. In particular, if you type `l^Ds`, that will
  run `ls`, though you won't be able to delete the `l` anymore since
  that was input before the `^D`. Also, if you type `ls^D^D`, that will
  log out just like typing `^D` on an empty line does. -- telotortium
  ([HN][])

[HN]: https://news.ycombinator.com/item?id=12437527
