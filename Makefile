# Compiler and linker
CXX = g++
LD = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -g  # Add -g for debugging symbols
# -Wall and -Wextra enable many warnings.  -O2 for optimization (use for release builds)

# Linker flags
LDFLAGS = -L/mingw64/lib # Adjust this if your SDL2 libs are elsewhere
# Libraries to link.  Order matters!  SDL2main FIRST, then SDL2, then SDL2_image.
LDLIBS = -lSDL2main -lSDL2 -lSDL2_image -lpng -ljpeg -lwebp

# Source files (add any new .cpp files here)
SRCS = src/Dino.cpp src/Game.cpp src/Obstacle.cpp src/main.cpp

# Object files (automatically generated from SRCS)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = DinoGame.exe

# Default target (build the executable)
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

# Rule to compile a .cpp file to a .o file
# The $< is the source file (e.g., src/Dino.cpp)
# The $@ is the target file (e.g., src/Dino.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target (remove object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)

#Phony targets tell make that these are not file names.
.PHONY: all clean