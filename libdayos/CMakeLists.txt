file(GLOB_RECURSE HEADERS *.h)
#file(GLOB_RECURSE SOURCES *.c*)
#file(GLOB_RECURSE ASM_SOURCES *.S)

set(ASM_SOURCES src/libc/signal-IA32.S)
set(SOURCES
	src/libc/assert.c
	src/libc/ctype.c
	src/libc/dirent.c
	src/libc/div.c
	src/libc/dlfcn.c
	src/libc/dlmalloc.c
	src/libc/environment.c
	src/libc/errno.c
	src/libc/exec.c
	src/libc/exit.c
	src/libc/fcntl.c
	src/libc/files.c
	src/libc/init.c
	src/dayos/interrupts.c
	src/libc/ioctl.c
	src/libc/locale.c
	src/libc/malloc.c
	src/dayos/memory.c
	src/dayos/message.c
	src/libc/optarg.c
	src/libc/printf.c
	src/libc/pthread.c
	src/libc/rand.c
	src/dayos/service.c
	src/libc/setjmp.c
	src/libc/signal.c
	src/libc/sleep.c
	src/libc/stack.c
	src/libc/stat.c
	src/libc/strconv.c
	src/libc/string.c
	src/dayos/syscall.c
	src/libc/time.c
	src/libc/utsname.c
	src/dayos/vfs.c
	src/libc/wait.c
	src/libc/getpid.c

    ${HEADERS}
)

enable_language(C ASM)

set(CMAKE_C_FLAGS "-m32 -Wall -g -fstack-protector-all -nostdinc -nodefaultlibs -pedantic-errors -D__dayos__")
set(CMAKE_ASM_FLAGS "-m32 -Wall -g -pedantic-errors")

include_directories("include" ${LIBDAYOS_INCLUDE} "../libmath")
add_library(dayos STATIC ${SOURCES} ${ASM_SOURCES} ${HEADERS})

# Tests
IF(NOT DISABLE_TESTS)
add_executable(tests.elf tests/main.c)
target_link_libraries(tests.elf dayos m)
ENDIF()

install(TARGETS dayos DESTINATION "${CMAKE_INSTALL_PREFIX}/usr/lib")
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}/usr")
