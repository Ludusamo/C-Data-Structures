SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRC_FILES := $(wildcard $(SRCDIR)/*.c)

RELEASE_SRC_FILES := $(filter-out main.c, $(SRC_FILES))
RELEASE_SRC_FILES := $(filter-out src/*_test.c, $(SRC_FILES))

OBJECTS :=  $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
RELEASE_OBJECTS :=  $(RELEASE_SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o.release)
rm = rm -f

CC = clang
COMPILER_FLAGS = -std=c99 -Wall -Iheader

LINKER = clang
LINKER_FLAGS = -Wall -Iheader

TARGET = cds

release: COMPILER_FLAGS += -O2 -fPIC

release: $(RELEASE_OBJECTS)
	$(CC) -shared -o $@ $(LINKER_FLAGS) $(RELEASE_OBJECTS)
	echo "Linking Complete!"

$(RELEASE_OBJECTS): $(OBJDIR)/%.o.release : $(SRCDIR)/%.c
	$(CC) $(RELEASE_COMPILER_FLAGS) -c $< -o $@
	echo "Compiled "$<" successfully!"

debug: $(OBJECTS)
	$(LINKER) $(BINDIR)/$(TARGET) $(LINKER_FLAGS) $(OBJECTS)
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
	$(rm) $(BINDIR)/$(TARGET)
	echo "Executable removed!"

memcheck:
	valgrind --leak-check=full --tool=memcheck $(BINDIR)/$(TARGET)

memcheckfull:
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck $(BINDIR)/$(TARGET)
