set(SOURCES
	src/IODevice.cpp
	src/HIDDevice.cpp
	src/CharDevice.cpp src/BlockDevice.cpp include/BlockDevice.h src/FileSystem.cpp include/FileSystem.h)

set(HEADERS 
	include/IODevice.h
	include/HIDDevice.h
	include/CharDevice.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fstack-protector-all -pedantic-errors -fno-builtin")

add_library(DriverKit STATIC ${SOURCES})
add_executable(dktest.elf tests/main.cpp)

include_directories("include" ${DAYOS_KERNEL_INCLUDE})
target_link_libraries(dktest.elf dayos m DriverKit)
