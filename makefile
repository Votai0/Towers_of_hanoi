all:clear compile run

clear:
	@clear

compile:
	@gcc -o test main.c -lm

run:
	@./test
