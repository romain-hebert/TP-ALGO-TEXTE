CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
TP = 1
PRGS = main

all: $(PRGS)

main: main.o trie.o
main.o: main.c trie.c

clean:
	$(RM) *.o *.log *tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	tar zcf HebertRomain-TP$(TP).tar.gz *.c *.h Makefile