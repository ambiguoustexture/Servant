all: $(patsubst %.c, %, $(wildcard *.c))

%: %.c makefile
	gcc -std=gnu99 -pedantic -pthread $< -o $@

# -pedantic: used in conjunction with -ansi,
# this tells the compiler to be adhere strictly to the ANSI standard,
# rejecting any code which is not compliant.

clean:
	rm $(patsubst %.c, %, $(wildcard *.c)) #-pthread
