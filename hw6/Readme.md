# C Log library

1. Git clone
2. gcc -c clog.c
3. ar rcs lib_cLog.a clog.o
4. gcc -o main main.c -L. -l_cLog
5. ./main
