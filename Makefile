CC = cc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/traverse.c src/sort.c
OBJ = ${SRC:.c=.o}
TARGET = my_ls

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
