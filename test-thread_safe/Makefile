PROJECT = test
CC = gcc
CFLAGS = -g -W -Wall -pthread
LIBS = -ldl -pthread
HEADER_FILE = ..	
CFLAGS += -I$(HEADER_FILE)
SOURCES = test.c \
	  ../malloc_count.c \
	  ../stack_count.c
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
OBJDUMP = objdump
all: $(PROJECT)

%.o: %.c $(HEADER_FILE)
	$(CC) -c $< -o $@ $(LIBS) $(CFLAGS)

$(PROJECT): $(OBJECTS)
	$(CC) $^ -o $@ $(LIBS) $(CFLAGS)
	$(OBJDUMP) -d $(PROJECT) > $(PROJECT).asm

.PHONY: clean
clean:
	rm -rf $(PROJECT)
	rm -rf *.asm
	find . -name "*.o" -exec rm {} \;