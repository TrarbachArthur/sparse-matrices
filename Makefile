all:
	gcc -o main *.c

run:
	./main

valgrind:
	valgrind --leak-check=full ./main

clean:
	rm main