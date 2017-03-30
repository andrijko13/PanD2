OBJS = main.cpp InitSDL.cpp LTexture.cpp
OBJ_NAME = prog.out

#Our compiler
CC = g++

#Compiler flags specifiec the additional compilation options we're using
COMPILER_FLAGS = -w

LINKER_FLAGS = -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_image -lpand2

all : $(OBJS)
	$(CC) -g $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
