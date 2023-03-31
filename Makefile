CC     = clang 
CFLAGS = -Wall -Werror -Wextra -Wpedantic -gdwarf-4

.PHONY: all clean

all: calc

calc: calc.o matrix.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< 
	
clean:
	rm -f calc matrix *.o
	
format: 
	clang-format -i -style=file *.[ch]
