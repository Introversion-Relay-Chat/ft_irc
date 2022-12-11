NAME			= ircserv

CPP				= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -MD
RM				= rm -f

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
CHECK = \033[0;32m\xE2\x9C\x94\033[0m

FUNC			=	main \
					Server \
					Channel \
					User \
					Utils \
					NumericReplies \
					Commands/PASS \
					Commands/NICK \
					Commands/USER \
					Commands/JOIN \
					Commands/PART \
					Commands/TOPIC \
					Commands/NAMES \
					Commands/LIST \
					Commands/INVITE \
					Commands/KICK \
					Commands/VERSION \
					Commands/TIME \
					Commands/ADMIN \
					Commands/INFO \

INC = ./include/Server.hpp \
		./include/Channel.hpp \
		./include/User.hpp \
		./include/Utils.hpp \

SRC_PATH = ./src/
SRC = $(addprefix $(SRC_PATH), $(addsuffix .cpp, $(FUNC)))

OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(FUNC)))

DEP_PATH = ./dep/
DEP = $(addprefix $(DEP_PATH), $(addsuffix .d, $(FUNC)))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INC:%=$(SRC_PATH)/%)
	@echo "$(NAME): $(GREEN) compiling... $< $(CHECK) $(RESET)"
	@$(CPP) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(SRC_PATH:%.cpp=$(OBJ_PATH)/%.o)
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
