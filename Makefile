CC = gcc
CFLAGS = -g  # Add any flags you need
TARGET = main
OBJS = main.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c


clean:
	rm -f $(TARGET) $(OBJS)