cmake_minimum_required(VERSION 3.28.0)

project(InOneWeekend)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 设置目标文件（.o 或 .obj 文件）输出目录
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/obj)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
# 添加可执行文件
add_executable(InOneWeekend src/inoneweekend.cpp)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件路径
target_include_directories(InOneWeekend PUBLIC src/include)


# 添加自定义库和依赖项（如果有）
# target_link_libraries(InOneWeekend SomeLibrary)

# 可以根据项目的实际需要进行更多的配置

