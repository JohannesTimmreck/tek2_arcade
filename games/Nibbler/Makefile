##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

SRC =	src/GameInterface.cpp	\
		src/Snake.cpp	\
		src/Text.cpp	\

OBJ =   $(SRC:.cpp=.o)

NAME    =	lib_arcade_nibbler.so

CXX =   g++

CXXFLAGS    =   -W -Wall -Werror -Wextra

%.o	: %.cpp
				@echo "Generation of the $@ file..."
				$(CXX) -fPIC -c -o $@ $<

all:    $(NAME)

$(NAME):	$(OBJ)
			@echo "Generation of the shared library $(NAME)..."
			$(CXX) -shared -o $(NAME) $(OBJ)
			mv $(NAME) ..

clean:
		@echo "deleting of object files..."
		$(RM) $(OBJ)

fclean: clean
		@echo "deleting of the shared library $(NAME)..."
		$(RM) ../$(NAME)

re: fclean all

.PHONY:	all $(NAME) clean fclean re