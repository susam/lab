Listings Experiments: Fonts, Columns, and Spaces
================================================
This directory contains LaTeX source code with a set of experiments that
demonstrate why the following parameters to `\lstset` command is
necessary while typesetting code listings with the `listings` package:

    \lstset{
        basicstyle=\ttfamily,
        columns=fullflexible,
        keepspaces=true
    }

These three parameters produce code listing that looks similar to code
listing in `verbatim` environment.

Further, for using straight quotes instead of curved quotes, the
following parameter is necessary:

    \lstset{
        upquote=true
    }

Additionally, it demonstrates that the following parameters are
necessary when the `language` parameter is used:

    \lstset{
        showstringspaces=false
    }

Here is an example of a minimal set of parameters necessary for
producing good quality code listing without syntax highlighting:

    \lstset{
        basicstyle=\ttfamily,
        columns=fullflexible,
        keepspaces=true,
        upquote=true
    }

Here is an example of a minimal set of parameters necessary for
producing good quality syntax highlighted code listing:

    \lstset{
        basicstyle=\ttfamily,
        columns=fullflexible,
        keepspaces=true,
        upquote=true,
        language=c,
        showstringspaces=false,
        commentstyle=\color{darkgray},
        directivestyle=\color{teal},
        keywordstyle=\color{blue},
        identifierstyle=\color{violet},
        stringstyle=\color{magenta}
    }

See the source and document below for actual code and output:

  - Source: [listings-fonts-columns-spaces.tex][SRC]
  - Output: [listings-fonts-columns-spaces.pdf][PDF]

[SRC]: listings-fonts-columns-spaces.tex
[PDF]: https://mycask.github.io/filebin/pdf/listings/listings-fonts-columns-spaces.pdf
