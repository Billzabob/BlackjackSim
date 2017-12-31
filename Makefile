OBJS = *.cpp
INCLUDES = *.hpp
CC = g++
COMPILER_FLAGS = -g -std=c++17 -Wall -Wextra -pedantic-errors
LINKER_FLAGS =
OBJ_NAME = bj

$(OBJ_NAME) : $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

clean :
	rm -rf $(OBJ_NAME)

run : $(OBJ_NAME)
	./$<

format : $(OBJS) $(INCLUDES)
	clang-format -i -style=Google $^
