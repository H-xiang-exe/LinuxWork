srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%,$(srcs))
#匹配模板，替换后的内容，查找的来源
all:$(objs)
	for i in $(objs);do gcc -o $$i $$i.c;done	
.PHONY:clean rebuild print
rebuild:clean $(out) $(objs)
clean:
	rm -rf $(objs)
print:
	@echo $(srcs)
	@echo $(objs)
