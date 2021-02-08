##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

SRC =   src/main.cpp	\
		src/Core.cpp	\
		src/MainMenu.cpp	\
		src/MainMenuObject.cpp	\

OBJ =   $(SRC:.cpp=.o)

NAME    =   arcade

CXX =   g++

CXXFLAGS    =   -W -Wall -Werror -Wextra -g

%.o	: %.cpp
				@echo "Generation of the $@ file..."
				$(CXX) -c -o $@ $<

all:    $(NAME)

$(NAME):	$(OBJ)
			@echo "Generation of the binary $(NAME)..."
			$(CXX) -o $(NAME) $(OBJ) -ldl
			mv $(NAME) ..

clean:
		@echo "deleting of object files..."
		$(RM) $(OBJ)

fclean: clean
		@echo "deleting of the binary $(NAME)..."
		$(RM) ../$(NAME)

re: fclean all

.PHONY:	all $(NAME) clean fclean re