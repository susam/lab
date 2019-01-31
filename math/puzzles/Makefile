# Compile most recently modified solution TeX file and view output PDF.
last:
	make view \
	FILE="$$(ls -t *.tex | grep -vE "^(preamble|begin|end)\.tex$$" | head -n 1)"

# Compile specified TeX file and view output PDF.
*.tex: FORCE
	make view FILE="$@"

# Compile all solution TeX files to PDFs.
all:
	ls -t *.tex | grep -vE "^(preamble|begin|end)\.tex$$" | \
	while read -r f; do \
	    make build FILE="$$f";
	done

# Compile TeX file specified in the FILE macro and view output PDF.
view:
	make build FILE="$(FILE)"
	FILE="$(FILE)"; make open FILE="$${FILE%.*}.pdf"

# Compile TeX file specified in the FILE macro.
build:
	pdflatex "$(FILE)"
	FILE="$(FILE)"; biber "$${FILE%.*}.bcf"
	pdflatex "$(FILE)"
	make clean
	FILE="$(FILE)"; make blob FILE="$${FILE%.*}.pdf"

# Open PDF file specified in the FILE macro with default application.
open:
	if command -v xdg-open > /dev/null; then \
	    xdg-open "$(FILE)"; \
	elif command -v open > /dev/null; then \
	    open "$(FILE)"; \
	else \
	    echo Cannot find xdg-open or open.; \
	fi

# Remove automatically generated files.
clean:
	rm -rf *.aux *.log *.out *.toc *.bbl *.bcf *.blg *.xml

DEST = ../../../blob/lab/math/puzzles
blob:
	mkdir -p "$(DEST)"
	cp "$(FILE)" "$(DEST)"

FORCE:
