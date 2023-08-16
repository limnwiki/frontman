SRC = ../src/main.cpp
NAME = frontman
FLAGS = -o $(NAME)

debug:
	g++ $(SRC) $(FLAGS) -Wall -Wextra -pedantic
	./$(NAME)
	
release:
	g++ $(SRC) $(FLAGS) -O2 -s

install:
	make release
	sudo mv $(NAME) /usr/bin/$(NAME)