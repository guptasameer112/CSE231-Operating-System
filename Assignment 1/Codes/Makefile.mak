all: compile run

compile:
	gcc shellinator.c -o shellinator
	gcc cat.c -o cat
	gcc ls.c -o ls
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm
	gcc date.c -o date
run:
	./shellinator