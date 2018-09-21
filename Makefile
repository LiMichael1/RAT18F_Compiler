CC=gcc
CFLAGS = -g -std=c11 -Wall -Wextra -Wpedantic -Werror \
	-Wfloat-equal -Wlogical-op -Wshadow -Wswitch-default \
	-Wbad-function-cast -Wcast-qual -Waggregate-return \
	-fno-diagnostics-show-option -D_POSIX_C_SOURCE=200801L

PROG = FSM
HDRS = fsm.h 
SRCS = main.cpp fsm.cpp

OBJS = $(SRCS:.cpp=.o)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o : main.cpp fsm.h fsm.cpp

fsm.o : fsm.h fsm.cpp

## Remove all the compilation and debugging files
clean :
	rm -f core $(PROG) $(OBJS)
