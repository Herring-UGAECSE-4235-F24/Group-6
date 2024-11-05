OBJS = expo.o
ifdef DEBUG
DEBUGFLGS = -g
else
DEBUGFLGS =
endif

%.o : %.s
	as -mfpu=vfpv3 $(DEBUGFLGS) $< -o $@
GPIO_OFF: $(OBJS)
	gcc -g -o expo $(OBJS) -lc

clean:
	rm *.o expo
