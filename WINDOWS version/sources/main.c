#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
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

Mix_Chunk *son;

int main(int argc, char *argv[]){
	
	char filePath[200];
	FILE* fichier = NULL;
	fichier = fopen("PATHROM.txt", "r");
	if(fichier != NULL){
		fscanf(fichier, "%[^\n]", filePath);
		fclose(fichier);
	}
	
	initSDL();
	initScreen();
	initPixel();
	initCpu();
	chargerFont();
	
	Uint8 loop = 1;
	Uint8 demarrer = 0;
	Uint8 compteur = 0;
	
	son=NULL;
	
	son = Mix_LoadWAV("sound/beep.wav");
	
	demarrer=chargerJeu(filePath) ;
	
	if(demarrer == 1){
		do{
			loop=listen() ; //afin de pouvoir quitter l'émulateur
			
			for(compteur=0; compteur<CPU_SPEED; compteur++) {
				interpreterOpcode(recupererOpcode()) ; 
			}
			
			if(cpu.compteurSon!=0) { 
				Mix_PlayChannel(0, son, 0); 
				cpu.compteurSon=0; 
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
    
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de Mixer 
     { 
        fprintf(stderr,"Problème d'initialisation de SDL_MIXER: %s",Mix_GetError()); 
        exit(EXIT_FAILURE); 
     } 
     Mix_AllocateChannels(1);
	
}

void quitSDL(){ 

    SDL_FreeSurface(square[0]); 
    SDL_FreeSurface(square[1]); 
    Mix_FreeChunk(son); 
    Mix_CloseAudio(); 
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
      
      return 0; 
    } 

} 

Uint8 listen() { 

Uint8 continuer=1; 

while(SDL_PollEvent(&event)) { 
        switch(event.type) {
			 
              case SDL_QUIT: {continuer = 0;break;}
              case SDL_KEYDOWN:{
								switch(event.key.keysym.sym) 
                                            { 
                                                case SDLK_KP0:{ cpu.touche[0x0]=1;break;} 
                                                case SDLK_KP7:{ cpu.touche[0x1]=1;break;} 
                                                case SDLK_KP8:{ cpu.touche[0x2]=1;break;} 
                                                case SDLK_KP9:{ cpu.touche[0x3]=1;break;}
                                                case SDLK_KP4:{ cpu.touche[0x4]=1;break;} 
                                                case SDLK_KP5:{ cpu.touche[0x5]=1;break;} 
                                                case SDLK_KP6:{ cpu.touche[0x6]=1;break;} 
                                                case SDLK_KP1:{ cpu.touche[0x7]=1;break;}
                                                case SDLK_KP2:{ cpu.touche[0x8]=1;break;} 
                                                case SDLK_KP3:{ cpu.touche[0x9]=1;break;} 
                                               case SDLK_KP_PERIOD:{ cpu.touche[0xA]=1;break;}
                                               case SDLK_KP_ENTER:{ cpu.touche[0xB]=1;break;}
                                               case SDLK_KP_MINUS:{ cpu.touche[0xC]=1;break;}
                                               case SDLK_KP_PLUS:{ cpu.touche[0xD]=1;break;}
                                               case SDLK_KP_MULTIPLY:{ cpu.touche[0xE]=1;break;}
                                               case SDLK_KP_DIVIDE:{ cpu.touche[0xF]=1;break;}
                                                default:{ break;} 
                                            } ;break;}
                                            
              case SDL_KEYUP:{
								switch(event.key.keysym.sym) 
                                            { 
                                                case SDLK_KP0:{ cpu.touche[0x0]=0;break;} 
                                                case SDLK_KP7:{ cpu.touche[0x1]=0;break;} 
                                                case SDLK_KP8:{ cpu.touche[0x2]=0;break;} 
                                                case SDLK_KP9:{ cpu.touche[0x3]=0;break;}
                                                case SDLK_KP4:{ cpu.touche[0x4]=0;break;} 
                                                case SDLK_KP5:{ cpu.touche[0x5]=0;break;} 
                                                case SDLK_KP6:{ cpu.touche[0x6]=0;break;} 
                                                case SDLK_KP1:{ cpu.touche[0x7]=0;break;}
                                                case SDLK_KP2:{ cpu.touche[0x8]=0;break;} 
                                                case SDLK_KP3:{ cpu.touche[0x9]=0;break;} 
                                               case SDLK_KP_PERIOD:{ cpu.touche[0xA]=0;break;}
                                               case SDLK_KP_ENTER:{ cpu.touche[0xB]=0;break;}
                                               case SDLK_KP_MINUS:{ cpu.touche[0xC]=0;break;}
                                               case SDLK_KP_PLUS:{ cpu.touche[0xD]=0;break;}
                                               case SDLK_KP_MULTIPLY:{ cpu.touche[0xE]=0;break;}
                                               case SDLK_KP_DIVIDE:{ cpu.touche[0xF]=0;break;}
                                                default:{ break;} 
                                            } ;break;}
                                            
                         default:{ break;}
	}

} 
    return continuer; 
}

