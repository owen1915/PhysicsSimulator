CC = clang
CFLAGS = -I/opt/homebrew/opt/sdl2/include -I/opt/homebrew/opt/sdl2/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2
TARGET = main

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LDFLAGS)

clean:
	rm -f $(TARGET)
