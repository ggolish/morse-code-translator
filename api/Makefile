CFLAGS = -Wall -g -Iinclude -fPIC
CC = gcc

.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CFLAGS) $*.c -o $*.o

OBJS = \
	src/fileio.c	\
	src/morse_translate.c	\
	src/scanner.c	\

TARGET = libmorse.so

default: $(TARGET)

$(TARGET): $(OBJS:.c=.o)
	$(CC) -shared -Wl,-soname,$(TARGET) $^ -o $(TARGET) -lc

morse: $(TARGET)
	gcc -g -Wall -Iinclude -Wl,-R -Wl,/home/ggolish/Developer/c/morse/api -o morse src/main.c libmorse.so

fileio.o: src/fileio.c include/fileio.h

main.o: src/main.c include/fileio.h include/morse_translate.h

morse_translate.o: src/morse_translate.c include/morse.h include/scanner.h

scanner.o: src/scanner.c include/scanner.h

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/fileio.o
	rm -f src/main.o
	rm -f src/morse_translate.o
	rm -f $(TARGET)
	rm -f morse
	rm -f src/scanner.o
