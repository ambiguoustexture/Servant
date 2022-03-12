## Static Library 
```Shell
# compile lib
cd src;
gcc *.c -c -I ../include;
ar rcs [libxxx.a] *.o;
mv *.a ../lib;
# link lib
gcc main.c -o main -I./include/ -lseq -L./lib/
```

### misc
ar: create, modify, and extract from archives
ar options:
    c: Create the archive.
    r: Insert the files member... into archive (with replacement).
    s: Write an object-file index into the archive, 
       or update an existing one, 
       even if no other change is made to the archive.
