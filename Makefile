NAME		=	TicTacToe-MachineLearning

CC			=	g++

SRCDIR		=	Src/
INCDIR		=	Include/

SRC			=	$(SRCDIR)Main.cpp \
				$(SRCDIR)Board.cpp \
				$(SRCDIR)AI.cpp \
				
OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	+=	-I $(INCDIR)
CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-O3

LDFLAGS		+=	-l sfml-system
LDFLAGS		+=	-l sfml-window
LDFLAGS		+=	-l sfml-graphics

%.o			:	%.cpp
				@$(CC) -c -o $@ $< $(CXXFLAGS)

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean		:
				@rm -f $(OBJ)

fclean		:	clean
				@rm -f $(NAME)

re			:	fclean all

debug		:	CXXFLAGS += -g3
debug		:	re
