# Common files
FLAGS = -Wall -Wextra -Wshadow -Werror -std=c99 -pedantic
# Compiler command, no debug
CC = gcc $(FLAGS)
# Compiler command in debug mode
CCD = $(CC) -DDEBUG -g
# Library files
LIB = lib/*.c

help:
	@echo "make [help]      -- print these instructions"
	@echo "make compile     -- compile basic union-find"
	@echo "make compile-ht  -- compile union-find with height tracking"
	@echo "make compile-pc  -- compile union-find with path compression"
	@echo "make kompile     -- compile Kruskal using basic union-find"
	@echo "make kompile-ht  -- compile Kruskal using union-find with height tracking"
	@echo "make kompile-pc  -- compile Kruskal using union-find with path compression"
	@echo "make run         -- run last compiled"
	@echo "make vrun        -- run last compiled with valgrind"
	@echo "make clean       -- remove temporary files"

# compile
compile: unionfind.c
	$(CCD) $(LIB) unionfind.c unionfind-test.c
compile-ht: unionfind-ht.c
	$(CCD) $(LIB) unionfind-ht.c unionfind-test.c
compile-pc: unionfind-pc.c
	$(CCD) $(LIB) unionfind-pc.c unionfind-test.c

kompile: unionfind.c kruskal.c
	$(CCD) $(LIB) unionfind.c kruskal.c kruskal-test.c
kompile-ht: unionfind-ht.c kruskal.c
	$(CCD) $(LIB) unionfind-ht.c kruskal.c kruskal-test.c
kompile-pc: unionfind-pc.c kruskal.c
	$(CCD) $(LIB) unionfind-pc.c kruskal.c kruskal-test.c

# run
run:
	./a.out

# run with valgrind
vrun:
	valgrind ./a.out

# clean up
clean:
	@rm -rf a.out *.dSYM *~
