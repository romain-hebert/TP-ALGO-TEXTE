CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
ARCHIVE_NAME = HebertRomain-TP
TP = 2
PRGS = text_gen word_gen test_search_algs search

all: $(PRGS)

text_gen: text_gen.c

word_gen: word_gen.c

search: search.c search_algs.o
search_algs.o: search_algs.c

test_search_algs: test_search_algs.c search_algs.o

clean_texts:
	$(RM) -r texts/
	$(RM) -r words/
clean:
	$(RM) *.o *.log *.tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	mkdir -p $(ARCHIVE_NAME)$(TP)
	cp *.c *.h *.sh makefile $(ARCHIVE_NAME)$(TP)/
	tar zcf $(ARCHIVE_NAME)$(TP).tar.gz $(ARCHIVE_NAME)$(TP)/
	$(RM) -r $(ARCHIVE_NAME)$(TP)/

