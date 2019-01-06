CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
INCLUDE         = -I../queue/inc
src 		= src/test_queue.cpp
obj 		= $(src:.cpp=.o)

CPPFLAGS      	+= $(INCLUDE)


test_queue:	$(obj) ../queue/libqueue.a
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
	rm -f $(obj) test_queue

.PHONY: libqueue
libqueue:
	make -f ../queue/MakefileLIB
