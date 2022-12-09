NAME			= ircserv

CPP				= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MD
RM				= rm -f

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;32m\xE2\x9C\x94\033[0m

FUNC			=	src/main \
					src/Server \
					src/User \
					src/Utils \
					src/NumericReplies \
					src/Commands/PASS \
					src/Commands/JOIN \

INC = ./src/IRC.h

SRC = $(addsuffix .cpp, $(FUNC))
OBJ = $(addsuffix .o, $(FUNC))
DEP = $(addsuffix .d, $(FUNC))

%.o: %.cpp
	@echo "$(NAME): $(GREEN) compiling... $< $(CHECK) $(RESET)"
	@$(CPP) $(CXXFLAGS) -I $(INC) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CPP) $(CXXFLAGS) -I $(INC) -o $(NAME) $(OBJ)
	@echo "$(NAME): $(GREEN) $(NAME) was created! $(CHECK) $(RESET)"

all: $(NAME)

clean :
	@$(RM) $(OBJ) $(DEP)
	@echo "$(NAME): $(RED) object files were deleted $(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(NAME): $(RED) $(NAME) was deleted $(RESET)"

re :
	@$(MAKE) fclean
	@$(MAKE) all

-include $(DEP)
