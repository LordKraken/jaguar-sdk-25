include $(JAGSDK)/tools/build/jagdefs.mk

JAGWIN = /mnt/c/Projects/Jaguar/dev/roms/
JCP=~/jaguar/bin/jcp

OBJS = \
startup.o \
jag.o

PROGS = jaghello.cof

jaghello.cof: $(OBJS)
	$(LINK) $(LINKFLAGS) -o $@ $(OBJS)
	mkdir -p $(JAGWIN)
	cp $(PROGS) $(JAGWIN)

go:	$(PROGS)
	$(JCP) $(PROGS)
	

include $(JAGSDK)/tools/build/jagrules.mk
