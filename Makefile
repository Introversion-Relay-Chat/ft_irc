SRCS			=	src/main.cpp \
					src/Server.cpp \
					src/User.cpp \
					src/Utils.cpp \
					src/NumericReplies.cpp \
					src/Commands/PASS.cpp \

OBJS			= $(SRCS:.cpp=.o)

CPP				= c++
RM				= rm -f
FLAGS			= -Wall -Wextra -Werror -std=c++98

NAME			= ircserv

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CPP) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CPP) $(FLAGS) -c -o $@ $<

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
