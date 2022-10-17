CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
ARCHIVE_NAME = HebertRomain-TP
TP = 1
PRGS = text_gen

all: $(PRGS)

text_gen: text_gen.o
text_gen.o: text_gen.c

clean:
	$(RM) text*.txt *.o *.log *.tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	mkdir -p $(ARCHIVE_NAME)$(TP)
	cp *.c *.h makefile $(ARCHIVE_NAME)$(TP)/
	tar zcf $(ARCHIVE_NAME)$(TP).tar.gz $(ARCHIVE_NAME)$(TP)/
	rm -r $(ARCHIVE_NAME)$(TP)/

