#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cpu.h"


#define CPU_SPEED 4 //nombre d'opération entre chaque frame. "Par tour de cpu"
#define FPS 16 //attente avant rafraichissement.

void initSDL();
void quitSDL();
void pause();
Uint8 chargerJeu(char *);
Uint8 listen();

int main(int argc, char *argv[]){
	
	
	initSDL();
	initScreen();
	initPixel();
	initCpu();
	chargerFont();
	
	Uint8 loop = 1;
	Uint8 demarrer = 0;
	Uint8 compteur = 0;
	
	demarrer=chargerJeu("/home/yoshi100/Bureau/dev/C/emuchip8/BC_test.ch8") ;
	
	if(demarrer == 1){
		do{
			loop=listen() ; //afin de pouvoir quitter l'émulateur
			
			for(compteur=0; compteur<CPU_SPEED; compteur++) { 
				interpreterOpcode(recupererOpcode()) ; 
			}
			
			updateScreen();
			decompter();
			SDL_Delay(FPS);
		}while(loop==1);

	}
			pause();
	
	return EXIT_SUCCESS;
}


void initSDL(){
	
	atexit(quitSDL);
	
	if(SDL_Init(SDL_INIT_VIDEO)==-1) { 
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL %s",SDL_GetError()); 
        exit(EXIT_FAILURE); 
    }
	
}

void quitSDL(){ 

    SDL_FreeSurface(square[0]); 
    SDL_FreeSurface(square[1]); 
    SDL_Quit(); 
} 

void pause(){
	Uint8 continuer = 1;
	
	do {
		SDL_WaitEvent(&event);
		switch(event.type) {
			 
             case SDL_QUIT: {
                    continuer=0; 
                    break; 
					}
					
             case SDL_KEYDOWN: {
                    continuer=0; 
                    break; 
					}
					
             default: {
				  break;
				  } 
             
         } 
		
	}while(continuer==1);
	
}

Uint8 chargerJeu(char *nomJeu) 
{ 
    FILE *jeu = NULL; 
    jeu = fopen(nomJeu,"rb"); 

    if(jeu != NULL) { 
        fread(&cpu.memoire[DEBUT_RAM],sizeof(Uint8)*(FULL_MEMORY-DEBUT_RAM), 1, jeu); 
        fclose(jeu); 
        return 1; 
    } 
    else { 
		printf("Error opening file: %s.\n", strerror(errno));
      perror("Error");
      return 0; 
    } 

} 

Uint8 listen() { 

Uint8 continuer=1; 

while(SDL_PollEvent(&event)) { 
        switch(event.type) {
			 
                case SDL_QUIT: {
					continuer = 0;
					break;
					}
					 
                case SDL_KEYDOWN:{
					continuer=0 ;
					break;
					} 
 
                default:{
					break;
					} 
            } 
} 
    return continuer; 
}
