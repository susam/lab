*.f: clean
	gfortran -std=f95 -pedantic -Wall -Wextra $@
	./a.out

*-real.f:
	@echo
	@echo ----------------------------------------------------------
	@echo Running without GNU extensions ...
	@echo ----------------------------------------------------------
	@echo
	-gfortran -std=f95 -pedantic -Wall -Wextra $@
	@echo
	@echo ----------------------------------------------------------
	@echo Running with GNU extensions ...
	@echo ----------------------------------------------------------
	@echo
	gfortran -pedantic -Wall -Wextra $@
	@echo
	./a.out

clean:
	rm -rf *.out
