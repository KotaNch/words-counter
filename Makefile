CC=clang
CFLAGS=-Wall -Wextra -std=c11 -O2

word-counter: src/main.c 
	$(CC) $(CFLAGS) -o $@ $<

test: word-counter
	sh tests/run.sh

clean:
	rm -f word-counter

.PHONY: test clean
