program_name 			:= environment_variables.bin

link_flags				:= -pipe

override compile_flags  += -MD -pipe

source_files 			:= $(wildcard *.c)

object_files      		:= $(source_files:.c=.o)

$(program_name): $(object_files)
	gcc -o $@ $^ $(link_flags) -Wall

%.o: %.c
	gcc $< -c $(compile_flags)

include $(wildcard *.d)

.PHONY: clean
clean:
	rm -f *.d *.o *.out *.bin *.a