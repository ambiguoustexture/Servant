all: $(patsubst %.c, %, $(wildcard *.c))

%: %.c makefile
	gcc $< -o $@ -std=gnu99 -pedantic

# -pedantic: used in conjunction with -ansi,
# this tells the compiler to be adhere strictly to the ANSI standard,
# rejecting any code which is not compliant.

clean:
	rm a.txt $(patsubst %.c, %, $(wildcard *.c))

