OBJS = fpEx1.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as -mfpu=vfpv3 $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o fpEx1 $(OBJS) -lc

clean:
	rm *.o fpEx1
