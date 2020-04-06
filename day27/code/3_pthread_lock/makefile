srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%,$(srcs))
CC:=gcc
%:%.c
	$(CC) $< -o $@ -lpthread  
.PHONY:clean rebuild
rebuild:clean $(objs)
clean:
	rm -rf $(objs) 
print:
	@echo $(srcs)
	@echo $(objs)
