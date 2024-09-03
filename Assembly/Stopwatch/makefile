OBJS = stopwatch.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o stopwatch $(OBJS) -lc

clean:
	rm *.o stopwatch