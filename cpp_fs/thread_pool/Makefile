
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS =  threadpool_test.cpp threadpool.cpp semaphore.cpp

# list of directories containing header files
PROJ_INC_DIR = $(ROOT_DIR)/cpp_fs/BTSqueue $(ROOT_DIR)/cpp_fs/function $(ROOT_DIR)/cpp_fs/semaphore/

# the executable file
PROJ_OUT = tp.out

# list of compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS = -std=c++11

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS = -pthread

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = $(ROOT_DIR)/cpp_fs/BTSqueue/Makefile $(ROOT_DIR)/cpp_fs/semaphore/Makefile

include $(ROOT_DIR)/make/Project.mak
