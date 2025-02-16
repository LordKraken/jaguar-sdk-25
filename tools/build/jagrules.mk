#====================================================================
#       Default Rules
#====================================================================

all: $(PROGS)

.SUFFIXES: .o .s .c

.s.o:
	$(ASM) $(ASMFLAGS) $< | sed 's|error|\x1b[0;31m&\x1b[0m|gI' | sed 's|warning|\x1b[0;33m&\x1b[0m|gI'

.c.o:
	$(CC) $(CDEFS) $(CINCLUDES) $(CFLAGS) -c -o $@ $< 2>&1 | sed 's|error|\x1b[0;31m&\x1b[0m|gI' | sed 's|warning|\x1b[0;33m&\x1b[0m|gI'
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
