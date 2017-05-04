
APP           = assembler

CC            = gcc
LINKER        = gcc -o
RM            = rm -f
MKDIR         = mkdir -p
RMDIR         = rmdir

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(SRCDIR)/as.c $(SRCDIR)/do0.c $(SRCDIR)/pseudo.c $(SRCDIR)/eval.c
SOURCES  += $(SRCDIR)/symtab.c  $(SRCDIR)/util.c $(SRCDIR)/ffwd.c $(SRCDIR)/output.c
INCLUDES := $(SRCDIR)/as.h $(SRCDIR)/table0.h
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DIRS     := $(OBJDIR) $(BINDIR)

all: directories $(BINDIR)/$(APP)

$(OBJECTS): $(OBJDIR)/%.o : $(SOURCES)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compiled "$@" successfully!"

$(BINDIR)/$(APP): $(OBJECTS)
	@$(LINKER) $@ $(LDFLAGS) $(OBJECTS)
	@echo "Linking complete!"

.PHONEY: directories
directories: $(DIRS)

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

$(BINDIR):
	@$(MKDIR) $(BINDIR)

.PHONEY: clean
clean:
	@$(RM) $(OBJDIR)/*
	@echo "Derived objects removed!"

.PHONEY: remove
realclean: clean
	@$(RM) $(BINDIR)/*
	@$(RMDIR) $(OBJDIR)
	@$(RMDIR) $(BINDIR)
	@echo "Binaries removed!"
