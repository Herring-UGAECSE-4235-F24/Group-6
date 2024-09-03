OBJS = Addressing.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -nostdlib -o Addressing $(OBJS) -lc

clean:
	rm *.o Addressing
