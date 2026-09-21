CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude -lm
TARGET = main
SRC = *.c
OBJ = *.o




$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)

debug:
	$(CC) -g $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: all clean run