LIBNAME = libPlayer.so

SOURCE_DIR = src

INCLUDE_DIR = inc

PLAYER_SOURCE = $(SOURCE_DIR)/player.cpp $(SOURCE_DIR)/simulation.cpp $(SOURCE_DIR)/simulatefield.cpp $(SOURCE_DIR)/graph.cpp $(SOURCE_DIR)/cycle.cpp $(SOURCE_DIR)/astar.cpp $(SOURCE_DIR)/util.cpp

COMMON_SOURCE = $(SOURCE_DIR)/playfield.cpp $(SOURCE_DIR)/snakeGraph.cpp $(SOURCE_DIR)/biconnected.cpp $(SOURCE_DIR)/cc.cpp $(SOURCE_DIR)/game.cpp

GRAPHICS = $(SOURCE_DIR)/application.cpp $(SOURCE_DIR)/main.cpp

DRIVER_SOURCE = $(SOURCE_DIR)/driver.cpp

COMMON_OBJS = $(COMMON_SOURCE:.cpp=.o)

PLAYER_OBJS = $(PLAYER_SOURCE:.cpp=.o)

GRAPHICS_OBJS = $(GRAPHICS:.cpp=.o)

DRIVER_OBJS = $(DRIVER_SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O3 -fPIC -shared -I $(INCLUDE_DIR)
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
	rm -rf $(SOURCE_DIR)/*.o $(SOURCE_DIR)/*.d core snake driver libPlayer.so

debug: CXXFLAGS = -DDEBUG -Wall -g -fPIC -shared -I $(INCLUDE_DIR)
debug: LIBS = -L. -lX11 -lGL -lpng -lpthread -lstdc++fs -ldl
debug: snake

debug_driver: CXXFLAGS = -DDEBUG -Wall -g -fPIC -shared -I $(INCLUDE_DIR)
debug_driver: LIBS = -L. -ldl
debug_driver: driver

tar: clean
	tar zcvf snake.tgz $(PLAYER_SOURCE) $(COMMON_SOURCE) $(DRIVER_SOURCE) $(GRAPHICS) $(INCLUDE_DIR)/*.h Makefile

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
