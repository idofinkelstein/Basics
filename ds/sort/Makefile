
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = bubble_sort.c insertion_sort.c merge_sort.c merge_sort_in_place.c selection_sort.c sort_test.c swap_bytes.c counting_sort.c quick_sort.c heap_sort.c heapify.c 

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/ds/heap

# the executable file
PROJ_OUT = sort.out

# list of compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS = NDEBUG

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/ds/heap/Makefile

include $(ROOT_DIR)/make/Project.mak
