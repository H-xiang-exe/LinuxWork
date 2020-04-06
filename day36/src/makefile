srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(srcs))
CC:=gcc
ELF:=server
CFLAGS:=-g -Wall 
$(ELF):$(objs)
	$(CC) -o $@ $^ -pthread
.PHONY:clean 
rebuild:clean 
clean:
	rm -rf $(objs) $(ELF)
