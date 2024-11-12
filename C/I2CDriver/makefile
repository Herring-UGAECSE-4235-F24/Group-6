OBJS = Pin21.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as  $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o Pin21 $(OBJS) -lc

clean:
	rm *.o Pin21
