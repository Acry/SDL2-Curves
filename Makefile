CFLAGS   = -Wall -Wextra -mtune=native `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lm -lSDL2_gfx

.SUFFIXES:
.SUFFIXES: .c .o

srcdir	 =src/
TARGETS	 = casteljau 1 2 3 4

.PHONY: all
all: $(TARGETS)

casteljau: $(srcdir)helper.c $(srcdir)4.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

1: $(srcdir)helper.c $(srcdir)1.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

2: $(srcdir)helper.c $(srcdir)2.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

3: $(srcdir)helper.c $(srcdir)3.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

4: $(srcdir)helper.c $(srcdir)4.c
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true

