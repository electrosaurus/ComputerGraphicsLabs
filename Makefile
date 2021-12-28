CXX = clang++
CXX_FLAGS = -std=c++11 -Iinclude
CPP = $(wildcard src/*.cpp)
OBJ = $(CPP:src/%.cpp=obj/%.o)
DEP = $(OBJ:%.o=%.d)

.PHONY: all clean

all: lab1 lab2

lab1: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) src/labs/lab1.cpp -o bin/lab1

lab2: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) src/labs/lab2.cpp -o bin/lab2

clean:
	rm -rf obj/*
	rm -rf bin/*

-include $(DEP)

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@
