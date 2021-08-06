sim: sim.o renderer.o util.o
	clang -o sim sim.o renderer.o util.o -framework GLUT -framework OpenGL -framework Cocoa

renderer.o: renderer.c
	clang -c renderer.c

util.o: util.c
	clang -c util.c

sim.o: sim.c macros.h renderer.h
	clang -c sim.c
