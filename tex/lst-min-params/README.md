Listings Minimal Parameters
===========================
[[TEX]] [[PDF]]

This directory contains LaTeX source code with a set of experiments that
demonstrate why the following parameters are necessary while typesetting
code listings with the `listings` package:

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

Additionally, the experiments demonstrate that the following parameter
is necessary when the `language` parameter is used:

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
producing good quality code listing with syntax highlighting:

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

  - Source: [[TEX]]
  - Output: [[PDF]]

[TEX]: lst-min-params.tex
[PDF]: https://susam.github.io/blob/lab/tex/lst-min-params/lst-min-params.pdf
