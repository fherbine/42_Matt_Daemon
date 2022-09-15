NAME = Matt_daemon
INCLUDES = ./includes
SRC_PATH = ./src
OBJ_PATH = $(SRC_PATH)/debug
SRC_NAMES = AReporter.abstract.cpp main.cpp Tintin_reporter.class.cpp Lock.class.cpp Server.class.cpp utility.cpp
OBJ_NAMES = $(SRC_NAMES:.cpp=.o)
SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAMES))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAMES))
IFLAGS = -I$(INCLUDES)
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror
DFLAGS = -g
CC = clang++

all: $(NAME)

welcome:
	@clear
	@figlet MattDaemon | lolcat 2>/dev/null
	@$(eval SHELL:=/bin/bash)
	@echo -e "\n"

$(OBJ_PATH):
	@mkdir $@
	@$(eval SHELL:=/bin/bash)
	@echo -e "\e[4;35mBuilding MattDaemon sources:\e[0m"

$(NAME): welcome $(OBJ_PATH) $(OBJS)
	@$(eval SHELL:=/bin/bash)
	@echo -e "✅ Source files: $(shell echo $(SRC_NAMES) | wc -w) / $(shell echo $(SRC_NAMES) | wc -w)\033[0m --> \033[1;32m[Done]\033[0m\n"
	@$(CC) $(DFLAGS) $(CPPFLAGS) -o $@ $(OBJS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@$(CC) $(CPPFLAGS) $(DFLAGS) $(IFLAGS) -c $? -o $@
	@$(eval SHELL:=/bin/bash)
	@echo -e "🔧 Source files: $(shell ls -1 $(OBJ_PATH) | wc -l) / $(shell echo $(SRC_NAMES) | wc -w)\r\c"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
