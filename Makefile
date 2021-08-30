sim: sim.o renderer.o util.o collision.o chemistry.o
	clang -o sim sim.o collision.o chemistry.o renderer.o util.o -framework GLUT -framework OpenGL -framework Cocoa

renderer.o: renderer.c
	clang -c renderer.c

collision.o: collision.c
	clang -c collision.c

chemistry.o: chemistry.c
	clang -c chemistry.c

util.o: util.c
	clang -c util.c

sim.o: sim.c macros.h renderer.h
	clang -c sim.c

tests: tests.o chemistry.o util.o collision.o
	clang -o tests tests.o chemistry.o util.o collision.o

tests.o: tests.c
	clang -c tests.c
