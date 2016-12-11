#ifndef PIXEL_H
#define PIXEL_H

#include <SDL/SDL.h>

//definition des macros

#define BLACK 0
#define WHITE 1

#define WIDTH_CHIP8 64	//largeur ecran chip 8
#define HEIGHT_CHIP8 32	//hauteur ecran chip 8

#define DIMPIXEL 8	//dimension du pixel par rapport à l'écran. Ici 1 pixel de la chip 8 aura la taille de 8 pixel de l'ordinateur.

#define WIDTH_WINDOW		WIDTH_CHIP8*DIMPIXEL		//Dimension de la fenetre d'execution.
#define HEIGHT_WINDOW		HEIGHT_CHIP8*DIMPIXEL		//Dimension de la fenetre d'execution.

typedef struct {
	SDL_Rect position; //position x, y pixel
	Uint8 color; //couleur pixel "noir/blanc"
} PIXEL;

SDL_Surface *screen, *square[2];		//on créer le pointeur de l'ecran et des pixels pour pouvoir les afficher avec les bonnes information par la suite.

PIXEL pixel [WIDTH_CHIP8] [HEIGHT_CHIP8];

SDL_Event event;

void initScreen();
void initPixel();
void dessinerPixel(PIXEL pixel);
void cleanScreen();
void updateScreen();
#endif
