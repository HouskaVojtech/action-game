# make, make all, make run, make clean, make doc, make compile

PROGRAM=houskvo2

CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb -lSDL2 -lSDL2_image

all: compile doc

run: compile
	./$(PROGRAM) examples/correct.map

compile: $(PROGRAM)

doc: src/main.cpp src/Vector2.h src/Game.h src/Entity.h 
	doxygen Doxyfile

$(PROGRAM): objs/main.o objs/Vector2.o objs/Game.o objs/Entity.o
	$(CC) $(CFLAGS) $^ -o $@

objs/main.o: src/main.cpp src/Game.h | objs
	$(CC) $(CFLAGS) -c $< -o $@

objs/Vector2.o: src/Vector2.cpp src/Vector2.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
	
objs/Game.o: src/Game.cpp src/Game.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
	
objs/Entity.o: src/Entity.cpp src/Entity.h | objs
	$(CC) $(CFLAGS) -c $< -o $@
	
objs: 
	mkdir objs
	
clean:
	rm -rf $(PROGRAM) objs/ doc/  2>/dev/null
