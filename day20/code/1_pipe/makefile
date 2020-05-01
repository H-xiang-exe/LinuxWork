srcs:=$(wildcard *.c)
ELFS:=$(patsubst %.c,%.o, $(srcs))
objs:=$(patsubst %.c,%,$(srcs))
all:$(objs)
	for i in $(objs);do gcc -o $$i $$i.c;done
.PHONY:clean rebuild
rebuild:clean $(objs)
clean:
	rm -rf $(objs) $(ELFS)
print:
	@echo $(srcs)
	@echo $(objs)
