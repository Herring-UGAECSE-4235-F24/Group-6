OBJS = PCLDR_6_2.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -nostdlib -g -o PCLDR_6_2 $(OBJS) -lc

clean:
	rm *.o PCLDR_6_2
