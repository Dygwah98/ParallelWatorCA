all: compile run clean

compile: source
	@g++ -o executable.out source/*.cc

run: executable.out
	@./executable.out

clean: executable.out
	@rm -f executable.out
