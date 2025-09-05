
CC = clang
CFLAGS = -g3 -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic

SRC = xd.c
OBJECT = $(SRC:.c=.o)
EXEC = xd

.PHONY: all clean 

all: $(EXEC)

$(EXEC): $(OBJECT)
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJECT) $(EXEC) 

 


