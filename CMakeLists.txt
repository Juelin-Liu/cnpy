CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(CNPY)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_STATIC "Build static (.a) library" ON)

include_directories(${ZLIB_INCLUDE_DIRS})

add_library(cnpy_mmap SHARED "cnpy_mmap.cpp")
target_link_libraries(cnpy_mmap ${ZLIB_LIBRARIES})
install(TARGETS "cnpy_mmap" LIBRARY DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

if(ENABLE_STATIC)
    add_library(cnpy_mmap_static STATIC "cnpy_mmap.cpp")
    set_target_properties(cnpy_mmap_static PROPERTIES OUTPUT_NAME "cnpy_mmap")
    install(TARGETS "cnpy_mmap_static" ARCHIVE DESTINATION lib)
endif(ENABLE_STATIC)

install(FILES "cnpy_mmap.h" DESTINATION include)
add_executable(mmap_example main.cc)
target_link_libraries(mmap_example cnpy_mmap)

find_package(ZLIB REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS})

add_library(cnpy SHARED "cnpy.cpp")
target_link_libraries(cnpy ${ZLIB_LIBRARIES})
install(TARGETS "cnpy" LIBRARY DESTINATION lib PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

if(ENABLE_STATIC)
    add_library(cnpy-static STATIC "cnpy.cpp")
    set_target_properties(cnpy-static PROPERTIES OUTPUT_NAME "cnpy")
    install(TARGETS "cnpy-static" ARCHIVE DESTINATION lib)
endif(ENABLE_STATIC)

install(FILES "cnpy.h" DESTINATION include)

install(FILES "mat2npz" "npy2mat" "npz2mat" DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
add_executable(example1 example1.cpp)
target_link_libraries(example1 cnpy)
