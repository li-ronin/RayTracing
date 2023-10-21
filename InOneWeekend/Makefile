CXX = g++
CXXFLAGS = -std=c++20 -O3
TARGET = ./bin/inoneweekend.exe

SRCS = ./src/inoneweekend.cpp ./src/ray.cpp ./src/vec3.cpp
OBJS = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

./obj/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 定义依赖关系
./obj/inoneweekend.o: ./src/inoneweekend.cpp ./src/ray.h
./obj/ray.o: ./src/ray.cpp ./src/ray.h ./src/vec3.h
./obj/vec3.o: ./src/vec3.cpp ./src/vec3.h

clean:
	rm -f $(TARGET) $(OBJS)
