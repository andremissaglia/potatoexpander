all:
	gcc -lm -g -o t3 *.c
run:
	./t3
c:
	./t3 < comp
	echo
d:
	./t3 < dec
	echo

test: all c d

val: all
	valgrind ./t3 < comp
	echo
	valgrind ./t3 < dec 
	echo
	
