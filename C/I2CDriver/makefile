OBJS = Pin26.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as  $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o Pin26 $(OBJS) -lc

clean:
	rm *.o Pin26
