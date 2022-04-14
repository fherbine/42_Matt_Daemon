NAME = Matt_daemon
INCLUDES = ./includes
SRC_PATH = ./src
OBJ_PATH = $(SRC_PATH)/debug
SRC_NAMES = AReporter.abstract.cpp main.cpp Tintin_reporter.class.cpp
OBJ_NAMES = $(SRC_NAMES:.cpp=.o)
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))
IFLAGS = -I$(INCLUDES)
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror
DFLAGS =
CC = clang++

all: $(NAME)

$(OBJ_PATH):
	@mkdir $@

$(NAME): $(OBJ_PATH) $(OBJS)
	@$(CC) $(DFLAGS) $(CPPFLAGS) -o $@ $(OBJS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@$(CC) $(CPPFLAGS) $(DFLAGS) $(IFLAGS) -c $? -o $@

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
