# options
CC=gcc
CFLAGS=-Wall
TARGET=bin/ipod

INCLUDES=-I/usr/include/gpod-1.0/gpod `pkg-config --cflags glib-2.0`

LDFLAGS=-lgpod `pkg-config --libs glib-2.0`

# globs
SRCS := $(wildcard src/*.c)
HDRS := $(wildcard src/*.h)
OBJS := $(patsubst src/%.c,bin/%.o,$(SRCS))

# link it all together
$(TARGET): $(OBJS) $(HDRS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

# compile an object based on source and headers
bin/%.o: src/%.c $(HDRS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# tidy up
clean:
	rm -f $(TARGET) $(OBJS)

all: $(TARGET)
	@echo "All done!"