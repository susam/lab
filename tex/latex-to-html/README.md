LaTeX to HTML
=============

 1. Enter the following command to convert file [foo.tex](foo.tex) to
    HTML with Pandoc `--standalone` option:

    ```sh
    make pandoc1
    ```

    The output file is available here: [foo-pandoc1.html].

    There are two issues with this solution:

      - The MathJax configuration code specified in
        [pandoc-standalone-head.html](pandoc-standalone-head.html) is
        inserted after the `<script>` tag that loads MathJax, so it has
        no effect.

      - The `align` environment are converted to `aligned` environment
        in the output, so equation numbering does not occur. As a
        result, the two `\eqref` commands lead to broken `(???)` links
        in the output.

 2. Enter the following command to convert [foo.tex](foo.tex) to HTML
    with Pandoc `--template` option:

    ```sh
    make pandoc2
    ```

    The output file is available here: [foo-pandoc2.html].

    While using our own template allows to specify MathJax configuration
    before loading MathJax, the issue about Pandoc converting `align`
    environment to `aligned` environment still remains.

[foo-pandoc1.html]: https://susam.github.io/blob/lab/tex/latex-to-html/foo-pandoc1.html
[foo-pandoc2.html]: https://susam.github.io/blob/lab/tex/latex-to-html/foo-pandoc2.html
