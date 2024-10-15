OBJS = Function6_14.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o Function6_14 $(OBJS) -lc

clean:
	rm *.o Function6_14
