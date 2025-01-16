##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##


CC = g++

CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC
SDL2FLAGS = `sdl2-config --cflags`
SDL2LIBS = `sdl2-config --libs` -lSDL2_ttf
SDL2IMAGELIBS = -lSDL2_image
NCURSESFLAGS = -lncurses

LIBSFLAGS = -lsfml-graphics -lsfml-window -lsfml-system $(SDL2LIBS) $(SDL2IMAGELIBS) $(NCURSESFLAGS)

RM = rm -f
RMDIR = rmdir

GRAPHICALS_DIR = graphicals
GAMES_DIR = games

GRAPHICAL_LIBS = $(shell find $(GRAPHICALS_DIR) -maxdepth 1 -mindepth 1 -type d -exec basename {} \;)
GAME_LIBS = $(shell find $(GAMES_DIR) -maxdepth 1 -mindepth 1 -type d -exec basename {} \;)

CORE = arcade

all: core graphicals games

core: $(CORE)

$(CORE):
	$(CC) $(CXXFLAGS) $(SDL2FLAGS) -o $@ $(wildcard src/*.cpp) $(LIBSFLAGS)

graphicals:
	mkdir -p lib
	@$(foreach lib,$(GRAPHICAL_LIBS),$(CC) $(CXXFLAGS) $(SDL2FLAGS) -shared -o ./lib/$(lib).so $(wildcard $(GRAPHICALS_DIR)/$(lib)/src/*.cpp) $(LIBSFLAGS);)

games:
	mkdir -p lib
	@$(foreach lib,$(GAME_LIBS),$(CC) $(CXXFLAGS) $(SDL2FLAGS) -shared -o ./lib/$(lib).so $(wildcard $(GAMES_DIR)/$(lib)/src/*.cpp) $(LIBSFLAGS);)

clean:
	$(RM) ./src/*.o

fclean: clean
	$(RM) $(CORE) ./lib/*.so
	if [ -d "./lib" ]; then $(RMDIR) lib; fi

re: fclean all

.PHONY: all clean fclean re core graphicals games

