#############################################################################
# Makefile for new 3D package demo
#############################################################################

include $(JAGSDK)/tools/build/jagdefs.mk

#############################################################################
# location of various directories
#############################################################################

INC=include
INC2=inc
LIB=lib
FONTDIR=fonts

#############################################################################
# names of various commands
#############################################################################

RM=rm -f
CFLAGS += -mshort -Wall -fno-builtin -nostdinc -I$(INC) -I$(INC2)

#
# rules for making things
#
.SUFFIXES: .o .3ds
.SUFFIXES: .cry .tga

.3ds.o:
	@echo "***** CONVERTING $< *****"
	3dsconv -o $*.s $< 
	$(ASM) $(ASMFLAGS) $*.s 
	$(RM) $*.s 

.tga.cry:
	tga2cry -binary $< 1> /dev/null

#############################################################################
# C library objects
# Normally we would put these into an archive (a .a file) and let the linker
# sort out which ones we need; for demo purposes, though, here they all are
# explicitly
#############################################################################
CRT0= $(LIB)/jagrt.o

LIBOBJS = $(LIB)/alloc.o $(LIB)/clock.o $(LIB)/ctype.o $(LIB)/font.o \
	$(LIB)/gpulib.o $(LIB)/joyinp.o $(LIB)/joypad.o $(LIB)/memset.o \
	$(LIB)/olist.o $(LIB)/sprintf.o $(LIB)/strcat.o $(LIB)/strcmp.o \
	$(LIB)/strcpy.o $(LIB)/strdup.o $(LIB)/strncmp.o $(LIB)/util.o \
	$(LIB)/video.o

SRCOBJS = asm/miscasm.o asm/trig.o asm/mkmat.o \
	asm/wfrend.o asm/gourrend.o asm/gourphr.o \
	asm/texrend.o asm/flattex.o asm/gstex.o \
	demo.o 

MODELS = 3ds/globe/globe.o 3ds/ship/ship.o \
	models/knight.o models/robot.o models/torus.o 

TEXTURES = 3ds/globe/c1.cry 3ds/globe/c2.cry 3ds/globe/c3.cry 3ds/globe/u1.cry 3ds/globe/u2.cry \
	3ds/globe/u3.cry 3ds/globe/l1.cry 3ds/globe/l2.cry 3ds/globe/l3.cry \
	3ds/ship/back3.cry 3ds/ship/bottom.cry 3ds/ship/bottomfr.cry 3ds/ship/engbot.cry 3ds/ship/engfrnt.cry \
	3ds/ship/engside.cry 3ds/ship/engtop.cry 3ds/ship/fin.cry 3ds/ship/finside.cry 3ds/ship/gunback.cry \
	3ds/ship/gunside.cry 3ds/ship/guntop.cry 3ds/ship/hood.cry 3ds/ship/roof.cry 3ds/ship/rtfront.cry \
	3ds/ship/rtside.cry 3ds/ship/winfrnt.cry 3ds/ship/wing.cry 3ds/ship/wingside.cry 3ds/ship/winrt.cry

GENERATED += $(TEXTURES)

PROGS = demo.cof

#############################################################################
# the textures are arranged in decreasing order of size
#############################################################################
FIXDATA = -ii 3ds/globe/c1.cry _c1 -ii 3ds/globe/c2.cry _c2 -ii 3ds/globe/c3.cry _c3 \
	-ii 3ds/globe/u1.cry _u1 -ii 3ds/globe/u2.cry _u2 -ii 3ds/globe/u3.cry _u3 \
	-ii 3ds/globe/l1.cry _l1 -ii 3ds/globe/l2.cry _l2 -ii 3ds/globe/l3.cry _l3 \
	-ii 3ds/ship/back3.cry _back3 -ii 3ds/ship/bottom.cry _bottom -ii 3ds/ship/bottomfr.cry _bottomfr \
	-ii 3ds/ship/engbot.cry _engbot -ii 3ds/ship/engfrnt.cry _engfrnt -ii 3ds/ship/engside.cry _engside \
	-ii 3ds/ship/engtop.cry _engtop -ii 3ds/ship/fin.cry _fin -ii 3ds/ship/finside.cry _finside \
	-ii 3ds/ship/gunback.cry _gunback -ii 3ds/ship/gunside.cry _gunside -ii 3ds/ship/guntop.cry _guntop \
	-ii 3ds/ship/hood.cry _hood -ii 3ds/ship/roof.cry _roof -ii 3ds/ship/rtfront.cry _rtfront \
	-ii 3ds/ship/rtside.cry _rtside -ii 3ds/ship/winfrnt.cry _winfrnt -ii 3ds/ship/wing.cry _wing \
	-ii 3ds/ship/wingside.cry _wingside -ii 3ds/ship/winrt.cry _winrt \
	-ii $(FONTDIR)/clr6x12.jft _usefnt

OBJS = $(CRT0) $(SRCOBJS) $(MODELS) $(LIBOBJS)

demo.cof: $(OBJS) $(TEXTURES)
	$(LINK) $(LINKFLAGS) -o demo.cof $(OBJS) $(FIXDATA)

#demo.cof: $(OBJS) $(TEXTURES)
#	$(LINK) $(LINKFLAGS) -a 802000 x x -o demo.cof $(OBJS) $(FIXDATA)
#$(DEMO).rom: $(DEMO).o
#    @$(RLN) -rw -z -n -a 802000 x x -o $@ $<
#
#.ONESHELL:
#$(DEMO).j64: $(DEMO).rom
#    @cat $(BJL_ROOT)/bin/Univ.bin $< >$@
#    cat $< >> $@
#inc/wfrend.o: inc/wfrend.s 
#inc/gourrend.o: inc/gourrend.s
#inc/gourphr.o: inc/gourphr.s
#inc/texrend.o: inc/texrend.s
#inc/flattex.o: inc/flattex.s
#inc/gstex.o: inc/gstex.s

include $(JAGSDK)/tools/build/jagrules.mk
