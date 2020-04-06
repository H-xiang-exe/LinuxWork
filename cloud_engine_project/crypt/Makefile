SRCS:=$(wildcard *.c)
ELFS:=$(SRCS:%.c=%)
CC:=gcc
all:$(ELFS)

%:%.c
	$(CC) $< -o $@ -lcrypt
clean:
	rm -rf $(ELFS)
