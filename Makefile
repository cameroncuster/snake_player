LIBNAME = libPlayer.so

PLAYER_SOURCE = player.cpp graph.cpp cycle.cpp astar.cpp

COMMON_SOURCE = playfield.cpp snakeGraph.cpp biconnected.cpp cc.cpp game.cpp

GRAPHICS = application.cpp main.cpp 

DRIVER_SOURCE = driver.cpp

COMMON_OBJS = $(COMMON_SOURCE:.cpp=.o)

PLAYER_OBJS = $(PLAYER_SOURCE:.cpp=.o)

GRAPHICS_OBJS = $(GRAPHICS:.cpp=.o)

DRIVER_OBJS = $(DRIVER_SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O3 -fPIC -shared
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -L. -lX11 -lGL -lpng -lpthread -lstdc++fs -ldl -lPlayer

.PHONY: clean

# Targets include all, clean, debug, tar

all : snake

snake: $(GRAPHICS_OBJS) $(COMMON_OBJS) libPlayer.so
	$(LINK) -o $@ $^ $(LIBS)

driver: $(DRIVER_OBJS) $(COMMON_OBJS) libPlayer.so
	$(LINK) -o $@ $^ $(LIBS)

libPlayer.so: $(PLAYER_OBJS)
	$(LINK) -o $@ $^ $(CXXFLAGS)

clean:
	rm -rf *.o *.d core snake driver libPlayer.so

debug: CXXFLAGS = -DDEBUG -Wall -g -fPIC -shared
debug: LIBS = -L. -lX11 -lGL -lpng -lpthread -lstdc++fs -ldl
debug: snake

debug_driver: CXXFLAGS = -DDEBUG -Wall -g -fPIC -shared
debug_driver: LIBS = -L. -ldl
debug_driver: driver

tar: clean
	tar zcvf snake.tgz $(SOURCE) *.h Makefile

help:
	@echo "	make snake  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

