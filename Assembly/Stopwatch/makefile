OBJS = stopwatch.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o stopwatch $(OBJS) -lc -lE4235

clean:
	rm *.o stopwatch
