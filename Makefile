SRCDIR = src
OBJDIR = obj
BINDIR = bin

TESTDIR = src/test

MKFILEPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURDIR := $(dir $(MKFILEPATH))

SRC_FILES := $(wildcard $(SRCDIR)/*.c)

TEST_SRC_FILES := $(wildcard $(TESTDIR)/*.c)

OBJECTS :=  $(SRC_FILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJECTS :=  $(TEST_SRC_FILES:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

CC = clang
CFLAGS = -std=c99 -Wall -Iheader -O2 -fPIC

TEST_CFLAGS = -std=c99 -Wall -Iheader -Iheader/test

LINKER_FLAGS = -Wall -Iheader

TARGET = cds

$(BINDIR)/lib$(TARGET).so: $(OBJECTS)
	$(CC) -shared -o $@ $(LINKER_FLAGS) $(OBJECTS)
	echo "Linking Complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	echo "Compiled "$<" successfully!"

debug: CFLAGS += -Iheader/test
debug: LINKER_FLAGS += -Iheader/test
debug: $(BINDIR)/lib$(TARGET).so
debug: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(TEST_OBJECTS)
	$(CC) -o $@ $(LINKER_FLAGS) -rpath $(CURDIR)bin $(TEST_OBJECTS) -L./bin -lcds
	echo "Linking Complete!"

$(TEST_OBJECTS): $(OBJDIR)/%.o : $(TESTDIR)/%.c
	$(CC) $(TEST_CFLAGS) -c $< -o $@
	echo "Compiled "$<" successfully!"

clean:
	$(RM) $(OBJECTS)
	echo "Cleanup complete!"

remove:
	make clean
	$(RM) $(BINDIR)/$(TARGET)
	$(RM) $(BINDIR)/lib$(TARGET).so
	echo "Executable removed!"

memcheck:
	valgrind --leak-check=full --tool=memcheck $(BINDIR)/$(TARGET)

memcheckfull:
	valgrind --leak-check=full --show-leak-kinds=all --tool=memcheck $(BINDIR)/$(TARGET)

.PHONY: memcheck memcheckfull remove clean debug release
