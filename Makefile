CXX = g++

COMPILE_FLAGS = -Wall -ggdb -O3
LINK_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

inc_dir = ./include
lib_dir = ./lib
src_dir = src/
obj_dir = ./objects/

src_files = $(wildcard */*.cpp */*/*.cpp )
objects = $(src_files:$(src_dir)/%.cpp=$(obj_dir)/%.o)

all: main

main: $(objects)
	$(CXX) -I$(inc_dir) -o $@ $^ -L$(lib_dir) $(LINK_FLAGS) 

.PHONY : clean
clean:
	-rm main $(objects)