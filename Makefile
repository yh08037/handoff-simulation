CFLAGS = -O
CC = gcc
SRC = main.c handoff_simulator.c
OBJ = $(SRC:.c = .o)

handoff_simulator: $(OBJ)
	$(CC) $(CFLAGS) -o NumTest $(OBJ)
clean:
	rm -f core *.o 