all:
	gcc -o main *.c

run: all
	./main

valgrind: all
	valgrind --leak-check=full ./main

clean:
	rm main