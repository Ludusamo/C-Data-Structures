SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRC_FILES := $(wildcard $(SRCDIR)/*.c)
OBJECTS :=  $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm = rm -f

CC = clang
COMPILER_FLAGS = -std=c99 -Wall -Iheader

LINKER = clang -o
LINKER_FLAGS = -Wall -Iheader -l cmocka

TARGET = cds

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LINKER) $@ $(LINKER_FLAGS) $(OBJECTS)
	echo "Linking Complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(COMPILER_FLAGS) -c $< -o $@
	echo "Compiled "$<" successfully!"

clean:
	$(rm) $(OBJECTS)
	echo "Cleanup complete!"

remove:
	make clean
	$(rm) $(BINDIR)/$(TARGET)
	echo "Executable removed!"

memcheck:
	valgrind --tool=memcheck $(BINDIR)/$(TARGET)
