CFLAGS=-g -Wall

OFILES= words.o hash.o unixtimer.o

all: words

words: $(OFILES)
	$(CC) $(CFLAGS) -o $@ $(OFILES)

clean:
	rm -rf *.o *~ words

fresh: clean all

