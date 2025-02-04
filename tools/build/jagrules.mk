#====================================================================
#       Default Rules
#====================================================================

# Define ANSI color codes
RED=\033[0;31m	# Red
NC=\033[0m		# No Color

all: $(PROGS)

.SUFFIXES: .o .s .c

.s.o:
	$(ASM) $(ASMFLAGS) $<

.c.o:
	$(CC) $(CDEFS) $(CINCLUDES) $(CFLAGS) -c -o $@ $< 2>&1 | sed 's/error/\x1b[0;31m&\x1b[0m/g'
#$(CC) $(CDEFS) $(CINCLUDES) $(CFLAGS) -c -o $@ $<

.c.s:
	$(CC) $(CDEFS) $(CINCLUDES) $(CFLAGS) -S -o $@ $<

$(CGPUOBJS):%o:%c
	$(CC_JRISC) $(CDEFS) $(CINCLUDES) $(CFLAGS_JRISC) -c $<

$(CDSPOBJS):%o:%c
	$(CC_JRISC) $(CDEFS) $(CINCLUDES) $(CFLAGS_JRISC) $(CFLAGS_DSP) -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS) $(GENERATED)
