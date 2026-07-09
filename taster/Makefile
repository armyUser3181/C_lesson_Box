CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Wno-implicit-fallthrough
TARGET = main
SRC = ../Main/main.c ../Node/Node.c ../Debugger/Debugger.c

all: run $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) 'tast code'

clean:
	rm -f $(TARGET)
