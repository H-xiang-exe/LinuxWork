out=main
srcs=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(srcs))
CC:=gcc
$(out):$(objs)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c $< -o $@ 
.PHONY:clean rebuild
rebuild:clean $(out) $(objs) 
clean:
	rm -rf $(objs) $(out) 
