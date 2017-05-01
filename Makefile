
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

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h) ../../include/image_mapping.h
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DIRS     := $(OBJDIR) $(BINDIR)

all: directories $(BINDIR)/$(APP)

$(SRCDIR)/first4kloader.h : ../spi_boot/bin/spi_boot.bin
	./spi_boot_header_generator.py $< ./$@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compiled "$<" successfully!"

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
