*.f: clean
	gfortran -std=f95 -pedantic -Wall -Wextra $@
	./a.out

gnu-10-real.f:
	@echo ----------------------------------------------------------
	@echo Running with GNU extensions ...
	@echo ----------------------------------------------------------
	@echo
	gfortran -pedantic -Wall -Wextra 10-real.f
	@echo
	./a.out

clean:
	rm -rf *.out
