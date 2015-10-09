CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

EXEC =  phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	watch -d -t ./phonebook_opt

clean:
	$(RM) $(EXEC) *.o perf.*
