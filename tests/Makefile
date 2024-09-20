CC = gcc
CFLAGS = -I.. -Wall -Wextra -std=c99
TARGET = test_uuid
SRC = test_uuid.c ../uuid.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
