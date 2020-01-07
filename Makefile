#
# http://www.gnu.org/software/make/manual/make.html
#

NAME     := elfexec
CC       ?= cc
SOURCES  := $(NAME).c
OBJECTS  := $(NAME).o
CFLAGS   := -ansi -pedantic -pedantic-errors -Wall -Werror -Wextra -Wconversion -O2
CPPFLAGS :=
LDFLAGS  :=

PREFIX   ?= /usr
BINDIR   := $(PREFIX)/bin
MANDIR   := $(PREFIX)/share/man

CFLAGS   += $(USER_CFLAGS)
CPPFLAGS += $(USER_CPPFLAGS)
LDFLAGS  += $(USER_LDFLAGS)

.PHONY: $(NAME) all clean install

all: $(NAME)

$(NAME): clean $(SOURCES) $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS) $(LDFLAGS)

clean:
	rm -f $(NAME)
	rm -f $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

install: $(NAME)
	mkdir -p $(abspath $(DESTDIR)/$(BINDIR))
	mkdir -p $(abspath $(DESTDIR)/$(MANDIR)/man1)
	install -m 0755 $(NAME) $(abspath $(DESTDIR)/$(BINDIR)/$(NAME))
	install -m 0644 $(NAME).1 $(abspath $(DESTDIR)/$(MANDIR)/man1/$(NAME).1)
