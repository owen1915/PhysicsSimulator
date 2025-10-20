CC = clang
CFLAGS = -I/opt/homebrew/opt/sdl2/include -I/opt/homebrew/opt/sdl2/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2

SRC = main.c window.c draw.c particle.c
OBJ = $(SRC:.c=.o)
OUT = main

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(OUT)
