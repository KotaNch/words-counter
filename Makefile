Cc=cc
CFLAGS=-Wall -Wextra -std=c11 -O2

word-counter: src/main.c 
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f word-counter
