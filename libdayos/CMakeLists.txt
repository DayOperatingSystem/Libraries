file(GLOB_RECURSE HEADERS *.h)
#file(GLOB_RECURSE SOURCES *.c*)
#file(GLOB_RECURSE ASM_SOURCES *.S)

set(ASM_SOURCES src/signal-IA32.S)
set(SOURCES
	src/assert.c
	src/buffer.c
	src/ctype.c
	src/dirent.c
	src/div.c
	src/dlfcn.c
	src/dlmalloc.c
	src/environment.c
	src/errno.c
	src/exec.c
	src/exit.c
	src/fcntl.c
	src/files.c
	src/init.c
	src/interrupts.c
	src/ioctl.c
	src/locale.c
	src/malloc.c
	src/memory.c
	src/message.c
	src/optarg.c
	src/printf.c
	src/pthread.c
	src/rand.c
	src/service.c
	src/setjmp.c
	src/signal.c
	src/sleep.c
	src/stack.c
	src/stat.c
	src/strconv.c
	src/string.c
	src/syscall.c
	src/time.c
	src/utsname.c
	src/vfs.c
	src/wait.c

    ${HEADERS}
)

enable_language(C ASM)

set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc -nodefaultlibs -pedantic-errors -fno-builtin -D__dayos__")
set(CMAKE_ASM_FLAGS "-m32 -Wall -g -pedantic-errors")

include_directories("include" ${LIBDAYOS_INCLUDE})
add_library(dayos STATIC ${SOURCES} ${ASM_SOURCES} ${HEADERS})

# Tests
IF(NOT DISABLE_TESTS)
add_executable(tests.elf tests/main.c)
target_link_libraries(tests.elf dayos m)
ENDIF()

install(TARGETS dayos DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}/usr")
