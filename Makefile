NAME			= ircserv

ARGUMENTS			=	6667 pass

CPP				= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
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
					Commands/OPER \
					Commands/QUIT \
					Commands/JOIN \
					Commands/PART \
					Commands/MODE \
					Commands/TOPIC \
					Commands/NAMES \
					Commands/LIST \
					Commands/INVITE \
					Commands/KICK \
					Commands/VERSION \
					Commands/TIME \
					Commands/ADMIN \
					Commands/INFO \
					Commands/KILL \
					Commands/WHO \
					Commands/WHOIS \
					Commands/WHOWAS \
					Commands/PRIVMSG \
					Commands/NOTICE \
					Commands/PING \
					Commands/PONG \

INC = ./include

SRC_PATH = ./src/
SRC = $(addprefix $(SRC_PATH), $(addsuffix .cpp, $(FUNC)))

OBJ_PATH = ./obj/
OBJ = $(addprefix $(OBJ_PATH), $(addsuffix .o, $(FUNC)))

DEP = $(addprefix $(OBJ_PATH), $(addsuffix .d, $(FUNC)))

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(dir $@)
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

debugflags:
	@$(eval CXXFLAGS += -MD -g -D DEBUG)

debug: debugflags all
	./$(NAME) $(ARGUMENTS)

-include $(DEP)
