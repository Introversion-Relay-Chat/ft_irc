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
					src/Channel \
					src/User \
					src/Utils \
					src/NumericReplies \
					src/Commands/PASS \
					src/Commands/NICK \
					src/Commands/USER \
					src/Commands/JOIN \
					src/Commands/PART \
					src/Commands/TOPIC \
					src/Commands/NAMES \
					src/Commands/LIST \

SRC = $(addsuffix .cpp, $(FUNC))
OBJ = $(addsuffix .o, $(FUNC))
DEP = $(addsuffix .d, $(FUNC))

%.o: %.cpp
	@echo "$(NAME): $(GREEN) compiling... $< $(CHECK) $(RESET)"
	@$(CPP) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@$(CPP) $(CXXFLAGS) -o $(NAME) $(OBJ)
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