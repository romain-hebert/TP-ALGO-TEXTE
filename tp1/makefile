CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
ARCHIVE_NAME = HebertRomain-TP
TP = 1
PRGS = test pref

all: $(PRGS)

test: test.c trie.o

pref: pref.c trie.o

trie.o: trie.c

clean:
	$(RM) *.o *.log *.tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	mkdir -p $(ARCHIVE_NAME)$(TP)
	cp *.c *.h makefile $(ARCHIVE_NAME)$(TP)/
	tar zcf $(ARCHIVE_NAME)$(TP).tar.gz $(ARCHIVE_NAME)$(TP)/
	rm -r $(ARCHIVE_NAME)$(TP)/

