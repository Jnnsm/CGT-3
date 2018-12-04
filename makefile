OBJ = Main.o
OBJ_NAME = jogo

CC=g++
CFLAGS=-g -std=c++11 -lglut -lGL -lGLU -lm

#Verifica o sistema operacional
ifeq ($(OS), Windows_NT)
    RM = del
else
    RM = rm
endif


all: $(OBJ)
	$(CC)  $(OBJ) $(CFLAGS) -o $(OBJ_NAME)

Main.o: Main.cpp Objeto.h Funcoes.h InputControl.h SceneLights.h ScreenDraw.h stb_image.h
	$(CC) -c Main.cpp $(CFLAGS)

.PHONY: clean clobber
clean:
	$(RM) $(OBJ)

clobber:
	$(RM) $(OBJ_NAME)
