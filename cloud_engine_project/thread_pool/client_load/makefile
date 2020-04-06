srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(srcs))
CC:=gcc
ELF:=client
CFLAGS:=-g -Wall 
$(ELF):$(objs)
	$(CC) -o $@ $^
.PHONY:clean 
rebuild:clean 
clean:
	rm -rf $(objs) $(ELF)
