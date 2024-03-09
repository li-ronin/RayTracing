# cmake_minimum_required(VERSION 3.28.0)

# project(TheNextWeek)

# # 设置可执行文件输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# # 设置目标文件（.o 或 .obj 文件）输出目录
# #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/obj)
# #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
# # 添加可执行文件
# add_executable(TheNextWeek src/thenextweek.cpp)

# # 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 添加头文件路径
# target_include_directories(TheNextWeek PUBLIC src/include)


# # 添加自定义库和依赖项（如果有）
# # target_link_libraries(InOneWeekend SomeLibrary)

# # 可以根据项目的实际需要进行更多的配置

cmake_minimum_required(VERSION 3.28)
project(00Test)

# 设置源文件路径
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${SOURCE_DIR}/include)
set(EXTERNAL_INCLUDE_DIR ${SOURCE_DIR}/external)  # 添加外部头文件目录  
  

# 将头文件目录添加到包含路径
include_directories(${INCLUDE_DIR})
include_directories(${EXTERNAL_DIR})

# # 将所有源文件列入变量
set(SOURCES
    ${INCLUDE_DIR}/test.cpp
    # ${INCLUDE_DIR}/camera.cpp
    # ${INCLUDE_DIR}/hittable_list.cpp
    # ${INCLUDE_DIR}/material.cpp
    # ${INCLUDE_DIR}/sphere.cpp
    # ${INCLUDE_DIR}/vec3.cpp
    # ${INCLUDE_DIR}/ray.cpp
    # ${INCLUDE_DIR}/aabb.cpp
    # ${INCLUDE_DIR}/bvh_node.cpp
    # ${INCLUDE_DIR}/texture.cpp
    # ${INCLUDE_DIR}/quad.cpp
)

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 生成可执行文件
add_executable(00Test ${SOURCES})

# 可以添加其他配置和依赖项（如果需要）
