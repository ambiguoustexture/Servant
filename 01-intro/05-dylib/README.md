## Static Library 
```Shell
# compile lib
cd src;
gcc *.c -c -I ../include -fpic;
gcc *.o -o libseq.so -shared
mv *.so ../lib;
# link lib
gcc main.c -o main -I./include/ -lseq -L./lib/

# append shared object to env 
## run the export command below or append it to ~/.*shrc
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:[absolute path of *.so]
## or append the export command to /etc/profile (su needed)
# append [absolute path of *.so] to /etc/ld.so.conf, then `sudo ldconfig`
# move *.so to /lib/ or /usr/lib/

### misc
ldd: print shared object dependencies 
