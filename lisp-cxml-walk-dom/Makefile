run:
	CL_SOURCE_REGISTRY="~/cl/code//" \
	ASDF_OUTPUT_TRANSLATIONS="$(HOME)/cl/code/:$(HOME)/cl/cache/" \
	sbcl --noinform --load walk.lisp --quit | tee out.txt

deps:
	rm -rf ~/cl/
	mkdir -p ~/cl/code/ ~/cl/cache/
	set -x; while read -r url; do curl -sSL "$$url" | tar -C ~/cl/code/ -xz; done < deps.txt
