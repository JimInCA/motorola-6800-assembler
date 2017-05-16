
APP        = as

CC         = gcc
LINKER     = gcc -o
RM         = rm -f
MKDIR      = mkdir -p
RMDIR      = rmdir

SRCDIR     = src
OBJDIR     = obj
BINDIR     = bin
TESTDIR    = test

CFLAGS    :=
LFLAGS    :=
DEPS      := $(SRCDIR)/as.h $(SRCDIR)/do.h $(SRCDIR)/eval.h $(SRCDIR)/globals.h
DEPS      += $(SRCDIR)/pseudo.h $(SRCDIR)/table.h $(SRCDIR)/ffwd.h
DEPS      += $(SRCDIR)/output.h $(SRCDIR)/symtab.h $(SRCDIR)/util.h
OBJ_6800  := $(OBJDIR)/do0.o $(OBJDIR)/table0.o
OBJ_6801  := $(OBJDIR)/do1.o $(OBJDIR)/table1.o
OBJ_6804  := $(OBJDIR)/do4.o $(OBJDIR)/table4.o
OBJ_6805  := $(OBJDIR)/do5.o $(OBJDIR)/table5.o
OBJ_6809  := $(OBJDIR)/do9.o $(OBJDIR)/table9.o
OBJ_6811  := $(OBJDIR)/do11.o $(OBJDIR)/table11.o
OBJ       := $(OBJDIR)/as.o $(OBJDIR)/eval.o $(OBJDIR)/symtab.o
OBJ       += $(OBJDIR)/util.o $(OBJDIR)/ffwd.o $(OBJDIR)/output.o $(OBJDIR)/pseudo.o
OBJ       += $(OBJDIR)/globals.o
DIRS      := $(OBJDIR) $(BINDIR)

all: directories $(BINDIR)/$(APP)0 $(BINDIR)/$(APP)1 $(BINDIR)/$(APP)4 $(BINDIR)/$(APP)5 $(BINDIR)/$(APP)9 $(BINDIR)/$(APP)11

6800: directories $(BINDIR)/$(APP)0

6801: directories $(BINDIR)/$(APP)1

6804: directories $(BINDIR)/$(APP)4

6805: directories $(BINDIR)/$(APP)5

6809: directories $(BINDIR)/$(APP)9

6811: directories $(BINDIR)/$(APP)11

directories: $(DIRS)

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

$(BINDIR):
	@$(MKDIR) $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo "Compiled "$@" successfully!"

$(BINDIR)/$(APP)0: $(OBJ) $(OBJ_6800)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

$(BINDIR)/$(APP)1: $(OBJ) $(OBJ_6801)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

$(BINDIR)/$(APP)4: $(OBJ) $(OBJ_6804)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

$(BINDIR)/$(APP)5: $(OBJ) $(OBJ_6805)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

$(BINDIR)/$(APP)9: $(OBJ) $(OBJ_6809)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

$(BINDIR)/$(APP)11: $(OBJ) $(OBJ_6811)
	$(LINKER) $@ $^ $(CFLAGS)
	@echo "Linking "$@" complete!"

clean:
	$(RM) $(OBJDIR)/*.o
	@echo "Derived objects removed!"

realclean: clean
	@$(RM) $(BINDIR)/* $(TESTDIR)/*.s19
	@$(RMDIR) $(OBJDIR)
	@$(RMDIR) $(BINDIR)
	@echo "Binaries removed!"

