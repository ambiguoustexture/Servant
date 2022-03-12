## Compiling a C executable
```Shell
gcc main.c -E -o main.i
gcc main.i -S -o main.s
gcc main.s -s -o main.o
```
or 
```Shell
gcc main.c -o main -save-temps -v
```

