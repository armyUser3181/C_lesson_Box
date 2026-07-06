CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main
SRC = main.c

all: run $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) 'tast code'

clean:
	rm -f $(TARGET)
