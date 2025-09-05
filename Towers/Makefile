CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = uniqcounter
HEADERS = item.h ll.h hash.h dictwords.h badhash.h

#all: toy
#all: toy bench1 bench2
all: toy bench1 bench2 uniqq

$(EXEC): $(EXEC).o  ll.o item.o hash.o 
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

toy: toy.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench1: dictwords_list.o abstractwords.o bench1.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench2: dictwords_hash.o abstractwords.o bench2.o hash.o ll.o item.o badhash.o
	$(CC) $^ $(LFLAGS) -o $@

uniqq: uniqq.o ll.o hash.o
	$(CC) $^ $(LFLAGS) -o $@

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

Bench1Check:
	valgrind --leak-check=full ./bench1

Bench2Check:
	valgrind --leak-check=full ./bench2




.PHONY: all clean format
