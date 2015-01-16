all:
	cd spooky && g++ spooky-c.cc -c && cd .. && gcc bench.c xxHash/xxhash.c spooky/spooky-c.o -o bench --std=c99;