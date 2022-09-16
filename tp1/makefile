CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
TP = 1
PRGS = main

all: $(PRGS)

main: main.c trie.c
	$(CC) $(CFLAGS) $? -o $@

clean:
	$(RM) *.o *tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	tar zcf HebertRomain-TP$(TP).tar.gz *.c *.h Makefile