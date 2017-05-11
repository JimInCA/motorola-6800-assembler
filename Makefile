
APP      = assembler

CC       = gcc
RM       = rm -f
MKDIR    = mkdir -p
RMDIR    = rmdir

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

CFLAGS  :=
DEPS    := $(SRCDIR)/as.h $(SRCDIR)/table0.h
OBJ     := $(OBJDIR)/as.o $(OBJDIR)/do0.o $(OBJDIR)/eval.o $(OBJDIR)/symtab.o
OBJ     += $(OBJDIR)/util.o $(OBJDIR)/ffwd.o $(OBJDIR)/output.o $(OBJDIR)/pseudo.o
OBJ     += $(OBJDIR)/globals.o
DIRS    := $(OBJDIR) $(BINDIR)

all: directories $(BINDIR)/$(APP)

directories: $(DIRS)

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

$(BINDIR):
	@$(MKDIR) $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	@echo "Compiled "$@" successfully!"

$(BINDIR)/$(APP): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Linking complete!"

clean:
	$(RM) $(OBJDIR)/*.o $(BINDIR)/$(APP)
	@echo "Derived objects removed!"

realclean: clean
	@$(RM) $(BINDIR)/*
	@$(RMDIR) $(OBJDIR)
	@$(RMDIR) $(BINDIR)
	@echo "Binaries removed!"

