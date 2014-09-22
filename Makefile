ifdef CLANG
CC 			= clang++
else
CC			= g++
endif

CFLAGS		= -c -g -pedantic -Wall -Wpointer-arith -Wcast-qual -std=c++11 \
			  -I./flat-2d/include -include src/NewMacro.h
LD			= g++
LDFLAGS 	= -L./flat-2d/lib/
RM			= rm
ECHO		= echo

LIBS 				= -lSDL2 -lCppUTest -lCppUTestExt -lflat-2d

OBJDIR				= obj
DEPS				= $(wildcard src/*.h)
EXECUTABLE 			= deadgaem
PROG_SOURCES 		= $(wildcard src/*.cpp)
PROG_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(PROG_SOURCES:.cpp=.o)))

TEST				= test
TEST_SOURCES 		= $(filter-out src/deadgaem.cpp,$(wildcard src/*.cpp)) $(wildcard testsrc/*.cpp)
TEST_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

LIBRARIES			= flat-2d

.PHONY: $(LIBRARIES) $(OBJDIR) clean

default: $(EXECUTABLE)

all: $(EXECUTABLE) $(TEST)

$(EXECUTABLE): $(LIBRARIES) $(OBJDIR) $(PROG_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(PROG_OBJECTS) $(LIBS) -o $@ 

check: $(TEST)
	./$(TEST) -v -c

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(TEST): $(LIBRARIES) $(TEST_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(TEST_OBJECTS) $(LIBS) -o $@

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: testsrc/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(LIBRARIES):
	$(MAKE) -C $@ 

clean:
	@$(ECHO) Cleaning project
	@$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)
	@for d in $(LIBRARIES); do (cd $$d; $(MAKE) clean ); done
