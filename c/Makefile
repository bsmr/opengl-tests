#
# Makefile
#

# freeglut is installed from source and lives in a non-default location.
# "-Wl,-rpath,$(GLUTLIB)" is used that "LD_LIBRARY_PATH" is not needed!

GLUTDIR	= /opt/freeglut/2.8.0
GLUTINC = $(GLUTDIR)/include
GLUTLIB = $(GLUTDIR)/lib

CC	= gcc
CFLAGS	= -Wall -O3
CINCS	= -I$(GLUTINC)

LD	= gcc
LDFLAGS	= -s -Wl,-rpath,$(GLUTLIB)
LDLIBS	= -L$(GLUTLIB) -lglut -lGLU

all:	oglbasic

oglbasic:	oglbasic.o
	$(LD) $(LDFLAGS) -o $@ $< $(LDLIBS)

oglbasic.o:	oglbasic.c
	$(CC) $(CFLAGS) $(CINCS) -o $@ -c $<

clean:
	rm -f *~
	rm -f *.o

nuke: clean
	rm -f oglbasic

#
# End Of File
#
