srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%,$(srcs))
all:$(objs)
	for i in $(objs);do gcc -o $$i $$i.c;done

.PHONY:clean rebuild
rebuild:clean $(objs)
clean:
	rm -rf $(objs) 
print:
	@echo $(srcs)
	@echo $(objs)
