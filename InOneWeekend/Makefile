CXX = g++
CXXFLAGS = -std=c++20 -O3
TARGET = ./bin/inoneweekend.exe

SRCS = ./src/inoneweekend.cpp
OBJS = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

./obj/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 定义依赖关系 
./obj/inoneweekend.o: ./src/inoneweekend.cpp  ./src/vec3.h ./src/camera.h ./src/sphere.h ./src/hittable_list.h ./src/material.h ./src/lambertian.h ./src/metal.h ./src/glass.h


clean:
	rm -f $(TARGET) $(OBJS)
