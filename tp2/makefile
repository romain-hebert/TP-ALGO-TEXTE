CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
ARCHIVE_NAME = HebertRomain-TP
TP = 1
PRGS = text_gen word_gen search_algs

all: $(PRGS)

text_gen: text_gen.c

word_gen: word_gen.c

search_algs: search_algs.c

clean:
	$(RM) text*.txt *.o *.log *.tar.gz
	$(RM) words/*
	$(RM) texts/*

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	mkdir -p $(ARCHIVE_NAME)$(TP)
	cp *.c *.h *.sh makefile $(ARCHIVE_NAME)$(TP)/
	tar zcf $(ARCHIVE_NAME)$(TP).tar.gz $(ARCHIVE_NAME)$(TP)/
	$(RM) -r $(ARCHIVE_NAME)$(TP)/

