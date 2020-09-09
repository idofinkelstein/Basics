
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = mt_memcpy.c mt_memcpy_test.c ws9.c

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/c

# the executable file
PROJ_OUT = mt_memcpy.out

# list of compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS = MT

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/c/Makefile

include $(ROOT_DIR)/make/Project.mak
