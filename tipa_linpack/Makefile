all:
	g++ main.c -o linpack -lm -pthread

run:
	g++ main.c -o linpack -lm -pthread
	./linpack		
test:
	g++ main.c -o linpack -lm -pthread -fsanitize=address
	./linpack	