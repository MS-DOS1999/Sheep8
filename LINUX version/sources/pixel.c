
#include "pixel.h"

void initPixel() {
	
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(x=0; x<WIDTH_CHIP8; x++){
		
		for(y=0; y<HEIGHT_CHIP8; y++){
			
			pixel [x] [y] .position.x  = x*DIMPIXEL;
			pixel [x] [y] .position.y = y*DIMPIXEL;
			pixel [x] [y] .color = BLACK;  // on met par default tous les pixels à zero
			
		}
		
	}
	
}

void initScreen(){
	screen  = NULL;
	square[0] = NULL;
	square[1] = NULL;
	
	screen = SDL_SetVideoMode(WIDTH_WINDOW, HEIGHT_WINDOW,32, SDL_HWSURFACE); //initialiser ecran
	SDL_WM_SetCaption("Sheep8 by Julien MAGNIN", NULL);
	
	if(screen==NULL) 		//vérifier si ecran s'initialise
    { 
        fprintf(stderr,"Erreur lors du chargement du mode vidéo %s",SDL_GetError()); 
        exit(EXIT_FAILURE); 
    } 
    
    
    square[0] = SDL_CreateRGBSurface(SDL_HWSURFACE,DIMPIXEL,DIMPIXEL,32,0,0,0,0);		//initialiser pixel noir
    if(square[0]==NULL) 		//verifier initialisation pixel noir
    { 
       fprintf(stderr,"Erreur lors du chargement de la surface %s",SDL_GetError()); 
       exit(EXIT_FAILURE); 
    } 
    SDL_FillRect(square[0], NULL, SDL_MapRGB(square[0]->format, 0x00, 0x00, 0x00)); //lui donner sa couleur "NOIR"
    
    
    square[1]=SDL_CreateRGBSurface(SDL_HWSURFACE,DIMPIXEL,DIMPIXEL,32,0,0,0,0); //initialiser pixel blanc 
    if(square[1]==NULL) 			//verifier initialisation pixel noir
    { 
       fprintf(stderr,"Erreur lors du chargement de la surface %s",SDL_GetError()); 
       exit(EXIT_FAILURE); 
    } 

    SDL_FillRect(square[1],NULL,SDL_MapRGB(square[1]->format,0xFF,0xFF,0xFF));		//lui donner sa couleur "BLANC"
}

void dessinerPixel(PIXEL pixel){
	SDL_BlitSurface(square[pixel.color], NULL, screen, &pixel.position);
}

void cleanScreen(){		//pour effacer l'ecran on remet tous les pixel à 0 donc en noir
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(x = 0; x<WIDTH_CHIP8; x++){
		
		for(y = 0; y<HEIGHT_CHIP8; y++){
			
			pixel[x][y].color=BLACK;
			
		}
		
	}
	
}

void updateScreen(){		//pour mettre à jour l'écran on dessine les pixels.
	Uint8 x = 0;
	Uint8 y = 0;
	
	for(x = 0; x<WIDTH_CHIP8; x++) {
		 
        for(y = 0; y<HEIGHT_CHIP8; y++) {
			 
             dessinerPixel(pixel[x][y]); 
             
        } 
        
    } 
    SDL_Flip(screen);		//Une fois les modifs faite on les mets sur l'écran.
}

