# 设置项目名称
cmake_minimum_required(VERSION 3.10)
project(AlgebraProject)

# 指定C编译器
set(CMAKE_C_COMPILER gcc)

# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/inc)

# 添加源文件并创建可执行文件
add_executable(AlgebraProject src/algebra.c src/main.c)

# （可选）设置C标准，例如使用C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)