cmake_minimum_required(VERSION 3.10)

project(PcCompression)


include_directories( "/home/ybh/intel/system_studio_2020/opencl/SDK/include" )
# LINK_DIRECTORIES("/home/ybh/intel/system_studio_2020/opencl/SDK/lib64")
# LINK_LIBRARIES(libOpenCL)

set(SRC_LIST main.cpp)
add_executable(pc_compression ${SRC_LIST})

target_link_libraries (pc_compression /home/ybh/intel/system_studio_2020/opencl/SDK/lib64/libOpenCL.so)
# target_link_libraries (opencl_test /usr/lib/x86_64-linux-gnu/intel-opencl/libigdrcl.so)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

