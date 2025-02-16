CFLAGS = -Wall
OBJ = .o
OBJS2CRY = tga2cry$(OBJ) cry$(OBJ) rgb$(OBJ) scale$(OBJ) palette$(OBJ)
OBJSINFO = tgainfo$(OBJ)
OBJSRGB = rgb2cry$(OBJ) cry$(OBJ)
OBJS = $(OBJS2CRY) $(OBJSINFO)
LDFLAGS = -lm
EXT =

all: tga2cry$(EXT) tgainfo$(EXT) rgb2cry$(EXT)

tga2cry$(EXT): $(OBJS2CRY)
	$(CC) -o tga2cry$(EXT) $(CFLAGS) $^ $(LDFLAGS)

tgainfo$(EXT): $(OBJSINFO)
	$(CC) -o tgainfo$(EXT) $(CFLAGS) $^

rgb2cry$(EXT): $(OBJSRGB)
	$(CC) -o rgb2cry$(EXT) $(CFLAGS) $^

.PHONY: clean
clean:
	$(RM) $(OBJS) tga2cry$(EXT) tgainfo$(EXT) rgb2cry$(EXT)
