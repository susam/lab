Structure and Interpretation of Computer Programs
=================================================

This document contains excerpts from the book *Structure and
Interpretation of Computer Programs*, second edition by Harold Abelson,
Gerald Jay Sussman, and Julie Sussman. Additionally, this document also
contains [notes](#notes) I took while studying the book.


Dedication
----------

This book is dedicated, in respect and admiration, to the spirit that
lives in the computer.

"I think that it's extraordinarily important that we in computer
science keep fun in computing. When it started out, it was an awful lot
of fun. Of course, the paying customers got shafted every now and then,
and after a while we began to take their complaints seriously. We began
to feel as if we really were responsible for the successful, error-free
perfect use of these machines. I don't think we are. I think we're
responsible for stretching them, setting them off in new directions,
and keeping fun in the house. I hope the field of computer science never
loses its sense of fun. Above all, I hope we don't become missionaries.
Don't feel as if you're Bible salesmen. The world has too many of those
already. What you know about computing other people will learn. Don't
feel as if the key to successful computing is only in your hands. What's
in your hands, I think and hope, is intelligence: the ability to see the
machine as more than when you were first led up to it, that you can make
it more."

---Alan J. Perlis (April 1, 1922 -- February 7, 1990)


Foreword
--------

It is better to have 100 functions operate on one data structure than to
have 10 functions operate on 10 data structures. ...

Alan J. Perlis\
New Haven, Connecticut


Preface to the Second Edition
-----------------------------

We have seen our students take the ideas and programs in this book and
build them in as the core of new computer systems and languages. In
literal realization of an ancient Talmudic pun, our students have become
our builders.


Preface to the First Edition
----------------------------

First, we want to establish the idea that a computer language is not
just a way of getting a computer to perform operations but rather that
it is a novel formal medium for expressing ideas about methodology.
Thus, programs must be written for people to read, and only incidentally
for machines to execute. ...

Underlying our approach to this subject is our conviction that "computer
science" is not a science and that its significance has little to do
with computers. The computer revolution is a revolution in the way we
think and in the way we express what we think. The essence of this
change is the emergence of what might best be called procedural
epistemology---the study of the structure of knowledge from an
imperative point of view, as opposed to the more declarative point of
view taken by classical mathematical subjects. Mathematics provides a
framework for dealing precisely with notions of "what is." Computation
provides a framework for dealing precisely with notions of "how to."


Acknowledgements
----------------

Marvin Minsky and Seymour Papert formed many of our attitudes about
programming and its place in our intellectual lives. To them we owe the
understanding that computation provides a means of expression for
exploring ideas that would otherwise be too complex to deal with
precisely. ...

We do not know who produced the Chinese edition, but we consider it an
honor to have been selected as the subject of an "unauthorized"
translation.


1. Building Abstractions with Procedures
----------------------------------------

We are about to study the idea of a *computational process*.
Computational processes are abstract beings that inhabit computers. As
they evolve, processes manipulate other abstract things called *data*.
The evolution of a process is directed by a pattern of rules called a
*program*. People create programs to direct processes. In effect, we
conjure the spirits of the computer with our spells.

...

Lisp was invented in the late 1950s as a formalism for reasoning about
the use of certain kinds of logical expressions, called *recursion
equations*, as a model for computation. The language was conceived by
John McCarthy and is based on his paper "Recursive Functions of Symbolic
Expressions and Their Computation by Machine" (McCarthy 1960).

...

The dialect of Lisp used in this book is called Scheme.

...


### 1.1 The Elements of Programming

A powerful programming language is more than just a means for
instructing a computer to perform tasks. The language also serves as a
framework within which we organize our ideas about processes. Thus, when
we describe a language, we should pay particular attention to the means
that the language provides for combining simple ideas to form more
complex ideas. Every powerful language has three mechanisms for
accomplishing this:

  - **primitive expressions**, which represent the simplest entities the
    language is concerned with,

  - **means of combination**, by which compound elements are built from
    simpler ones, and

  - **means of abstraction**, by which compound elements can be named
    and manipulated as units.

...


#### 1.1.1 Expressions

Expressions such as these, formed by delimiting a list of expressions
within parentheses in order to denote procedure application, are called
*combinations*. The leftmost element in the list is called the
*operator*, and the other elements are called *operands*. The value of a
combination is obtained by applying the procedure specified by the
operator to the *arguments* that are the values of the operands.


#### 1.1.2 Naming and the Environment

A critical aspect of a programming language is the means it provides for
using names to refer to computational objects. We say that the name
identifies a *variable* whose *value* is the object.

...

It should be clear that the possibility of associating values with
symbols and later retrieving them means that the interpreter must
maintain some sort of memory that keeps track of the name-object pairs.
This memory is called the *environment* (more precisely the *global
environment*, since we will see later that a computation may involve a
number of different environments).


Notes
-----

This section contains additional notes taken by me. These are not
excerpts from the book.

### Videos

Related video lectures by Hal Abelson and Gerald Jay Sussman are
available [here][ocw videos]. There are 20 videos in total.

[ocw videos]: https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-001-structure-and-interpretation-of-computer-programs-spring-2005/video-lectures/

There is also a Youtube playlist for these videos here:
https://www.youtube.com/playlist?list=PLE18841CABEA24090

As of 26 Oct 2019, there are 40 videos in this playlist. The 20 videos
have been uploaded twice to this playlist: once on 8-9 Apr 2009 and once
again on 23 Aug 2019.
