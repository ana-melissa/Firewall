SOURCES = $(wildcard *.c)
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g
LDFLAGS = -lm
OBJECTS = $(SOURCES:%.c=%.o)

EXEC = banhammer

all: $(EXEC)

$(EXEC): $(OBJECTS)
		$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	
%.o: %.c
		$(CC) $(CFLAGS) -c $<

# tidy:
#		rm -rf $(OBJECTS)

clean:
		rm -rf $(EXEC) $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]

# debug: CFLAGS += -g
# debug: all

