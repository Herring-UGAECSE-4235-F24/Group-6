OBJS = printloop.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -o printloop $(OBJS) -lE4235

clean:
	rm *.o printloop
