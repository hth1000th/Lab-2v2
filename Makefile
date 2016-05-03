all: main.c queue.c scheduler.c switch.c
	gcc -o main main.c queue.c scheduler.c switch.c -I .

run:
	./main

clean:
	rm -f main
	rm -f t

test1: test_queue.c
	gcc -o t test_queue.c queue.c -I .
	./t
	rm -f t

test2: test_scheduler.c
	gcc -o t test_scheduler.c scheduler.c queue.c switch.c -I .
	./t
	rm -f t
