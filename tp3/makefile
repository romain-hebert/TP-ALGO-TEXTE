CC = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=500 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -fstack-protector-all -O2 -pthread
ARCHIVE_NAME = HebertRomain-TP
TP = 3
PRGS = genere-texte genere-mots ac-matrice ac-hachage

all: $(PRGS)

genere-texte: genere-texte.c

genere-mots: genere-mots.c

clean:
	$(RM) *.o *.tar.gz

mdproper: clean
	$(RM) $(PRGS)

tar: mdproper
	mkdir -p $(ARCHIVE_NAME)$(TP)
	cp *.c *.h *.txt *.sh makefile $(ARCHIVE_NAME)$(TP)/
	tar zcf $(ARCHIVE_NAME)$(TP).tar.gz $(ARCHIVE_NAME)$(TP)/
	$(RM) -r $(ARCHIVE_NAME)$(TP)/

