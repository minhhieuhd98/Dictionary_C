all: 
	gcc -o main main.c `pkg-config gtk+-3.0 --cflags --libs` -w
	
