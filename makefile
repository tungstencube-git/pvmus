CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lncurses

SRCDIR = src
OBJ = $(SRCDIR)/main.o $(SRCDIR)/player.o $(SRCDIR)/scanner.o $(SRCDIR)/ui.o
TARGET = pvmus
INSTALL_DIR = /usr/local/bin

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

install: $(TARGET)
	install -d $(DESTDIR)$(INSTALL_DIR)
	install -m 755 $(TARGET) $(DESTDIR)$(INSTALL_DIR)

uninstall:
	rm -f $(DESTDIR)$(INSTALL_DIR)/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean install uninstall
