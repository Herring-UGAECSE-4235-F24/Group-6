OBJS = scantest.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o scantest $(OBJS) -lc -lE4235

clean:
	rm *.o scantest
