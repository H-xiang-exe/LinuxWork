out:=main
srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(srcs))
$(out):$(objs)
	gcc -o $@ $^
%.o:%.c
	gcc -c $< -o $@
.PHONY:clean rebuild
rebuild:clean $(out) $(objs)
clean:
	rm -rf $(objs) $(out)
print:
	@echo $(srcs)
	@echo $(objs)
