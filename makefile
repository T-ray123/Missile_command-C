IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

LDIR=lib
SDIR=src
ODIR=obj
TARGET=target

LIBS=-lmenu -lncurses -lm

_DEPS = \
    main.h \
    input_layer.h \
    animate.h \
    canvas.h \
    alien_layer.h \
    defense_layer.h \
    collision_layer.h \
    ui_layer.h \
    main_menu.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = \
    main.o \
    input_layer.o \
    animate.o \
    canvas.o \
    alien_layer.o \
    defense_layer.o \
    collision_layer.o \
    ui_layer.o \
    main_menu.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_setup := $(shell mkdir -p $(ODIR) $(TARGET))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

missile_command: $(OBJ)
	$(CC) -o $(TARGET)/$@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
