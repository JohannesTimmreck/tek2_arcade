##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

SRC =	src/GraphicalInterface_sdl2.cpp	\
	  	src/Asset.cpp	\

OBJ =   $(SRC:.cpp=.o)

NAME    =	lib_arcade_sdl2.so

CXX =   g++

CXXFLAGS    =   -W -Wall -Werror -Wextra

%.o	: %.cpp
				@echo "Generation of the $@ file..."
				$(CXX) -fPIC -c -o $@ $<

all:    $(NAME)

$(NAME):	$(OBJ)
			@echo "Generation of the shared library $(NAME)..."
			$(CXX) -shared -o $(NAME) $(OBJ) -lSDL2 -lSDL2_image -lSDL2_ttf
			mv $(NAME) ..

clean:
			@echo "deleting of object files..."
			$(RM) $(OBJ)

fclean: 	clean
			@echo "deleting of the shared library $(NAME)..."
			$(RM) ../$(NAME)

re: fclean all
