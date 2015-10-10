CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -DORIGINAL -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -DHASHFUNCTION -o $@ \
		$(SRCS_common) $@.c

perf:
	echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh
	perf stat -r 10 -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses ./phonebook_opt
	perf stat -r 10 -e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses ./phonebook_orig

run: $(EXEC)
	watch -d -t ./phonebook_orig

clean:
	$(RM) $(EXEC) *.o perf.*
