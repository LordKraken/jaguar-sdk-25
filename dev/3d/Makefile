###############################################################################
# Makefile for new 3D package demo
###############################################################################

include $(JAGSDK)/tools/build/jagdefs.mk

###############################################################################
# location of various directories
###############################################################################

INC=include
INC2=inc
LIB=lib
LIBASM=libasm
FONTDIR=fonts

###############################################################################
# names of various commands
###############################################################################

RM=rm -f
CFLAGS += -mshort -Wall -fno-builtin -nostdinc -I$(INC) -I$(INC2)

###############################################################################
# rules for making things
###############################################################################

.SUFFIXES: .o .3ds
.SUFFIXES: .cry .tga

.3ds.o:
	@echo "***** CONVERTING $< *****"
	3dsconv -o $*.s $< 
	$(ASM) $(ASMFLAGS) $*.s 
	$(RM) $*.s 

.tga.cry:
	tga2cry -binary $< 1> /dev/null

###############################################################################
# C library objects
# Normally we would put these into an archive (.a file) and let the linker sort
# out which ones we need; for demo purposes, though, they all are explicitly
###############################################################################

CRT0 = $(LIBASM)/jagrt.o 

LIBOBJSASM = $(LIBASM)/clock.o $(LIBASM)/gpulib.o $(LIBASM)/joyinp.o \
	$(LIBASM)/memset.o $(LIBASM)/memcpy.o $(LIBASM)/util.o \
	$(LIBASM)/video.o

LIBOBJS = $(LIB)/alloc.o  $(LIB)/ctype.o $(LIB)/font.o \
	 $(LIB)/joypad.o $(LIB)/olist.o $(LIB)/sprintf.o \
	 $(LIB)/strcat.o $(LIB)/strcmp.o $(LIB)/strcpy.o \
	 $(LIB)/strdup.o $(LIB)/strncmp.o
	

SRCOBJS = asm/miscasm.o asm/trig.o asm/mkmat.o \
	asm/wfrend.o asm/gourrend.o asm/gourphr.o \
	asm/texrend.o asm/flattex.o asm/gstex.o \
	models/cube.o \
	source/camera.o \
	source/models.o \
	source/object.o \
	source/renderer.o \
	source/rendertools.o \
	source/scene.o \
	source/screen.o \
	source/tools.o \
	source/game.o \
	source/main.o

MODELS = models/castle/castle.o \
	models/globe/globe.o \
	models/radar/radar.o \
	models/ship/ship.o \
	models/cube2/cube2.o \
	models/feisar/feisar.o \
	models/knight.o \
	models/robot.o \
	models/torus.o 

TEXTURES_AS_TGA = $(wildcard models/*/*.tga)
TEXTURES = $(patsubst %.tga, %.cry, $(TEXTURES_AS_TGA))

GENERATED += $(TEXTURES)

PROGS = demo.cof

###############################################################################
# the textures are arranged in decreasing order of size
###############################################################################

#CRY_FILES_USED = $(wildcard 3ds/globe/*.cry) $(wildcard 3ds/ship/*.cry)
CRY_FILES = $(shell ls -S models/globe/*.cry models/radar/*.cry models/ship/*.cry models/cube2/*.cry)
FIXDATA = $(foreach file, $(CRY_FILES), -ii $(file) _$(basename $(notdir $(file)))) \
		-ii $(FONTDIR)/clr6x12.jft _usefnt

OBJS = $(CRT0) $(SRCOBJS) $(MODELS) $(LIBOBJS) $(LIBOBJSASM)

$(PROGS): $(OBJS) $(TEXTURES)
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

all:
#@echo $(TEXTURES)
#@echo $(CRY_FILES)