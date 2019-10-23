CC = gcc
CFLAGS = -fPIC -shared
GUILE = `pkg-config --cflags --libs guile-2.2`
SDL2 = `sdl2-config --cflags --libs` -lSDL2_ttf
OUTDIR = lib

libguile-ascii.so: src/ascii.c
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ $^ $(GUILE) $(SDL2)
