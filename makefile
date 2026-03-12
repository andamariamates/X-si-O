CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses
TARGET = game.out
SRCS = main.c gui.c tic_tac_toe.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c gui.h tic_tac_toe.h
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)
