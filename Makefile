CC=g++
CFLAGS= -I/usr/local/include/ -I/usr/local/include/SDL
LDFLAGS=-lSDL_ttf -lSDL_mixer -lSDL_gfx -lSDL_image -I/usr/local/include/ -I/usr/local/include/SDL
SDLFLAGS=`sdl-config --cflags --libs`
SOURCES=SDLMain.m unicode.cpp mysdl.cpp node.cpp screen.cpp abstract_inputnode.cpp arrow.cpp background.cpp ball.cpp ballmanager.cpp cancelnode.cpp continuenode.cpp debug.cpp fx.cpp game.cpp grid.cpp highscoremanager.cpp highscorenode.cpp highscorescreen.cpp homescreen.cpp inputnode.cpp lib.cpp main.cpp menu.cpp music.cpp newgamenode.cpp points.cpp scorescrollnode.cpp settingscreen.cpp settingsnode.cpp sound.cpp sprite.cpp submitnode.cpp vector.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=km-bubble-shooter

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm ./km-bubble-shooter

$(EXECUTABLE):
	$(CC) $(LDFLAGS) $(SDLFLAGS) $(SOURCES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(SDLFLAGS) $< -o $@

.m.o:
	$(CC) $(CFLAGS) $(SDLFLAGS) $< -o $@
