ifdef CLANG
CC 			= clang++
else
CC			= g++
endif

# ECHO colors
CNORMAL	= \033[0m
CGREEN	= \033[32m

SDL2_LDFLAGS		:= $(shell sdl2-config --static-libs)
SDL2_CFLAGS			:= $(shell sdl2-config --cflags)

CFLAGS		= -c -g -pedantic -Wall -Wpointer-arith -Wcast-qual -std=c++11 \
			  -I./flat/include -I./include -include src/NewMacro.h $(SDL2_CFLAGS) -DDEBUG
LD			= g++
LDFLAGS 	= -L./flat/lib/ -L./lib/
RM			= rm
ECHO		= echo -e
CP			= cp
MV			= mv
LIBS 		= $(SDL2_LDFLAGS) -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lCppUTest -lCppUTestExt -lflat

OBJDIR				= obj
DEPS				= $(wildcard src/*.h)
EXECUTABLE 			= deadgaem
PROG_SOURCES 		= $(wildcard src/*.cpp)
PROG_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(PROG_SOURCES:.cpp=.o)))

TEST				= test
TEST_SOURCES 		= $(filter-out src/deadgaem.cpp,$(wildcard src/*.cpp)) $(wildcard testsrc/*.cpp)
TEST_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

LIBRARIES			= flat

.PHONY: $(LIBRARIES) $(OBJDIR) libs default dist clean cleanall check checkall

default: 
	@$(MAKE) --no-print-directory libs
	@$(ECHO) "$(CGREEN)Building $(EXECUTABLE)...$(CNORMAL)"
	@$(MAKE) --no-print-directory $(EXECUTABLE)
	@$(ECHO) "$(CGREEN)Building $(EXECUTABLE) complete$(CNORMAL)"

all: default checkall

run:
	@$(MAKE) --not-print-directory libs
	@$(MAKE) --no-print-directory $(EXECUTABLE)
	@./$(EXECUTABLE)

check: 
	@$(MAKE) --no-print-directory libs
	@$(MAKE) --no-print-directory $(TEST)
	@./$(TEST) -v -c

checkall:
	@$(MAKE) --no-print-directory libs
	@for d in $(LIBRARIES); do (cd $$d; $(MAKE) --no-print-directory check ); done
	@$(MAKE) --no-print-directory $(TEST)
	@./$(TEST) -v -c

libs: $(LIBRARIES)

dist: default
	$(LD) $(LDFLAGS) -Wl,-rpath,'.:lib/.' $(PROG_OBJECTS) $(LIBS) -o dist/$(EXECUTABLE)

$(EXECUTABLE): $(PROG_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(PROG_OBJECTS) $(LIBS) -o $@ 

$(TEST): $(TEST_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(TEST_OBJECTS) $(LIBS) -o $@

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: testsrc/%.cpp
	$(CC) $(CFLAGS) $< -o $@

$(LIBRARIES):
	@$(ECHO) "$(CGREEN)Building $@lib...$(CNORMAL)"
	@$(MAKE) -C $@ 
	@$(ECHO) "$(CGREEN)Building $@lib complete$(CNORMAL)"

clean:
	@$(ECHO) Cleaning project
	@$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)

cleanall:
	@$(ECHO) Cleaning project and all libraries
	@for d in $(LIBRARIES); do (cd $$d; $(MAKE) --no-print-directory clean ); done
	@$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)
