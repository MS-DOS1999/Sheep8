#ifndef CPU_H
#define CPU_H

#include "pixel.h"

#define FULL_MEMORY 4096
#define DEBUT_RAM 512
#define NOMBRE_OPCODE 35

typedef struct {
	Uint8 memoire[FULL_MEMORY]; //memoire chip 8
	Uint8 V[16]; //registres 16 au total sans le registre d'adresse
	Uint16 I; //registre d'adresse 
	Uint16 pile[16]; //pile : peut stocker 16 adresse mémoire qui ont été sauté. Gère les sauts dans "memoire".
	Uint8 nombreSaut; //stock le nombre de saut pour que ça e depasse pas 16.
	Uint8 compteurCPU; //cadence la vitesse de calcul
	Uint8 compteurSon; //permet de jouer des sons
	Uint16 programCounter; //permet de parcourir le tableau "memoire" initialisé à 16 bit car le tableau à une longueur de 4096 . 
														//Uint8 va de 0 à 255. Uint16 va de 0 à 65 535. 
	
} CPU;

CPU cpu; //declaration de la variable cpu avec comme base la matrice "CPU"

typedef struct { 
    Uint16 masque [NOMBRE_OPCODE];   //la Chip 8 peut effectuer 35 opérations, chaque opération possédant son masque 
    Uint16 id[NOMBRE_OPCODE];   //idem, chaque opération possède son propre identifiant 

}JUMP;

JUMP jp;


void initCpu() ;
void decompter();
Uint16 recupererOpcode() ;
void chargerFont();
void initialiserJump () ;
Uint8 recupererAction(Uint16) ;
void interpreterOpcode(Uint16) ;
void dessinerEcran(Uint8 ,Uint8 , Uint8 );
#endif
