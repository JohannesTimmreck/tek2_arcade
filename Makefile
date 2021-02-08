##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

all: core games graphicals

core:
		@echo "Build core"
		make -C core

games:
		@echo "Build games"
		make -C games/Nibbler
		make -C games/Pacman

graphicals:
		@echo "Build graphicals"
		make -C lib/nCurses
		make -C lib/SFML
		make -C lib/SDL2


clean:
	make clean -C core
	make clean -C games/Nibbler
	make clean -C games/Pacman
	make clean -C lib/nCurses
	make clean -C lib/SFML
	make clean -C lib/SDL2

fclean:
	make fclean -C core
	make fclean -C games/Nibbler
	make fclean -C games/Pacman
	make fclean -C lib/nCurses
	make fclean -C lib/SFML
	make fclean -C lib/SDL2

re: fclean all

.PHONY: all core games graphicals clean fclean re