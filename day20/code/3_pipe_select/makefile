srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%,$(srcs))
all:$(objs)
	for i in $(objs);do gcc -o $$i $$i.c;done
.PHONY:clean rebuild print
rebuild:clean $(objs)
clean:
	rm -rf $(objs) 
