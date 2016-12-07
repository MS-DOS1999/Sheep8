#include <SDL/SDL.h>
#include "cpu.h"

void initCpu() {			//on initialise le CPU donc tous les objets de la matrice précedemment créer dans la library  "cpu.h"
	
	Uint16 i = 0;
	
	for(i=0; i<FULL_MEMORY; i++){ 				//on initialise la mémoire en utilisant une boucle "for" sur ça taille.
		cpu.memoire[i] = 0;
	}
	
	for(i=0; i<16; i++){			//initialisation du registre et de la pile
		cpu.V[i] = 0;
		cpu.pile[i] = 0;
	}
	
	cpu.programCounter = DEBUT_RAM; 		//on initialise le program counter à 512 qui est le debut de la RAM.
	cpu.I = 0;
	cpu.nombreSaut = 0;
	cpu.compteurCPU = 0;
	cpu.compteurSon = 0;
	
	initialiserJump();
	
}

void decompter() {
	
	if(cpu.compteurCPU>0){
		cpu.compteurCPU--;
	}
	if(cpu.compteurSon>0){
		cpu.compteurSon--;
	}
	
}

Uint16 recupererOpcode() {  
    return (cpu.memoire[cpu.programCounter]<<8) + cpu.memoire[cpu.programCounter+1]; 
}

void chargerFont() { 
    cpu.memoire[0]=0xF0;cpu.memoire[1]=0x90;cpu.memoire[2]=0x90;cpu.memoire[3]=0x90; cpu.memoire[4]=0xF0; // O 

    cpu.memoire[5]=0x20;cpu.memoire[6]=0x60;cpu.memoire[7]=0x20;cpu.memoire[8]=0x20;cpu.memoire[9]=0x70; // 1 

    cpu.memoire[10]=0xF0;cpu.memoire[11]=0x10;cpu.memoire[12]=0xF0;cpu.memoire[13]=0x80; cpu.memoire[14]=0xF0; // 2 

    cpu.memoire[15]=0xF0;cpu.memoire[16]=0x10;cpu.memoire[17]=0xF0;cpu.memoire[18]=0x10;cpu.memoire[19]=0xF0; // 3 

    cpu.memoire[20]=0x90;cpu.memoire[21]=0x90;cpu.memoire[22]=0xF0;cpu.memoire[23]=0x10;cpu.memoire[24]=0x10; // 4 

    cpu.memoire[25]=0xF0;cpu.memoire[26]=0x80;cpu.memoire[27]=0xF0;cpu.memoire[28]=0x10;cpu.memoire[29]=0xF0; // 5 

    cpu.memoire[30]=0xF0;cpu.memoire[31]=0x80;cpu.memoire[32]=0xF0;cpu.memoire[33]=0x90;cpu.memoire[34]=0xF0; // 6 

    cpu.memoire[35]=0xF0;cpu.memoire[36]=0x10;cpu.memoire[37]=0x20;cpu.memoire[38]=0x40;cpu.memoire[39]=0x40; // 7 

    cpu.memoire[40]=0xF0;cpu.memoire[41]=0x90;cpu.memoire[42]=0xF0;cpu.memoire[43]=0x90;cpu.memoire[44]=0xF0; // 8 

    cpu.memoire[45]=0xF0;cpu.memoire[46]=0x90;cpu.memoire[47]=0xF0;cpu.memoire[48]=0x10;cpu.memoire[49]=0xF0; // 9 

    cpu.memoire[50]=0xF0;cpu.memoire[51]=0x90;cpu.memoire[52]=0xF0;cpu.memoire[53]=0x90;cpu.memoire[54]=0x90; // A 

    cpu.memoire[55]=0xE0;cpu.memoire[56]=0x90;cpu.memoire[57]=0xE0;cpu.memoire[58]=0x90;cpu.memoire[59]=0xE0; // B 

    cpu.memoire[60]=0xF0;cpu.memoire[61]=0x80;cpu.memoire[62]=0x80;cpu.memoire[63]=0x80;cpu.memoire[64]=0xF0; // C 

    cpu.memoire[65]=0xE0;cpu.memoire[66]=0x90;cpu.memoire[67]=0x90;cpu.memoire[68]=0x90;cpu.memoire[69]=0xE0; // D 

    cpu.memoire[70]=0xF0;cpu.memoire[71]=0x80;cpu.memoire[72]=0xF0;cpu.memoire[73]=0x80;cpu.memoire[74]=0xF0; // E 

    cpu.memoire[75]=0xF0;cpu.memoire[76]=0x80;cpu.memoire[77]=0xF0;cpu.memoire[78]=0x80;cpu.memoire[79]=0x80; // F 

}

void initialiserJump () { 

  jp.masque[0]= 0x0000; jp.id[0]=0x0FFF;          /* 0NNN */ 
  jp.masque[1]= 0xFFFF; jp.id[1]=0x00E0;          /* 00E0 */ 
  jp.masque[2]= 0xFFFF; jp.id[2]=0x00EE;          /* 00EE */ 
  jp.masque[3]= 0xF000; jp.id[3]=0x1000;          /* 1NNN */ 
  jp.masque[4]= 0xF000; jp.id[4]=0x2000;          /* 2NNN */ 
  jp.masque[5]= 0xF000; jp.id[5]=0x3000;          /* 3XNN */ 
  jp.masque[6]= 0xF000; jp.id[6]=0x4000;          /* 4XNN */ 
  jp.masque[7]= 0xF00F; jp.id[7]=0x5000;          /* 5XY0 */ 
  jp.masque[8]= 0xF000; jp.id[8]=0x6000;          /* 6XNN */ 
  jp.masque[9]= 0xF000; jp.id[9]=0x7000;          /* 7XNN */ 
  jp.masque[10]= 0xF00F; jp.id[10]=0x8000;          /* 8XY0 */ 
  jp.masque[11]= 0xF00F; jp.id[11]=0x8001;          /* 8XY1 */ 
  jp.masque[12]= 0xF00F; jp.id[12]=0x8002;          /* 8XY2 */ 
  jp.masque[13]= 0xF00F; jp.id[13]=0x8003;          /* BXY3 */ 
  jp.masque[14]= 0xF00F; jp.id[14]=0x8004;          /* 8XY4 */ 
  jp.masque[15]= 0xF00F; jp.id[15]=0x8005;          /* 8XY5 */ 
  jp.masque[16]= 0xF00F; jp.id[16]=0x8006;          /* 8XY6 */ 
  jp.masque[17]= 0xF00F; jp.id[17]=0x8007;          /* 8XY7 */ 
  jp.masque[18]= 0xF00F; jp.id[18]=0x800E;          /* 8XYE */ 
  jp.masque[19]= 0xF00F; jp.id[19]=0x9000;          /* 9XY0 */ 
  jp.masque[20]= 0xF000; jp.id[20]=0xA000;          /* ANNN */ 
  jp.masque[21]= 0xF000; jp.id[21]=0xB000;          /* BNNN */ 
  jp.masque[22]= 0xF000; jp.id[22]=0xC000;          /* CXNN */ 
  jp.masque[23]= 0xF000; jp.id[23]=0xD000;          /* DXYN */ 
  jp.masque[24]= 0xF0FF; jp.id[24]=0xE09E;          /* EX9E */ 
  jp.masque[25]= 0xF0FF; jp.id[25]=0xE0A1;          /* EXA1 */ 
  jp.masque[26]= 0xF0FF; jp.id[26]=0xF007;          /* FX07 */ 
  jp.masque[27]= 0xF0FF; jp.id[27]=0xF00A;          /* FX0A */ 
  jp.masque[28]= 0xF0FF; jp.id[28]=0xF015;          /* FX15 */ 
  jp.masque[29]= 0xF0FF; jp.id[29]=0xF018;          /* FX18 */ 
  jp.masque[30]= 0xF0FF; jp.id[30]=0xF01E;          /* FX1E */ 
  jp.masque[31]= 0xF0FF; jp.id[31]=0xF029;          /* FX29 */ 
  jp.masque[32]= 0xF0FF; jp.id[32]=0xF033;          /* FX33 */ 
  jp.masque[33]= 0xF0FF; jp.id[33]=0xF055;          /* FX55 */ 
  jp.masque[34]= 0xF0FF; jp.id[34]=0xF065;          /* FX65 */ 

}

Uint8 recupererAction(Uint16 opcode) { 
    Uint8 action; 
    Uint16 resultat; 

    for(action=0; action<NOMBRE_OPCODE; action++) { 
        resultat = (jp.masque[action]&opcode);  /* On récupère les bits concernés par le test, l'identifiant de l'opcode */ 

        if(resultat == jp.id[action]){/* On a trouvé l'action à effectuer */ 
           break; /* Plus la peine de continuer la boucle car la condition n'est vraie qu'une seule fois*/ 
		}
  }

    return action;  //on renvoie l'indice de l'action à effectuer 
}

void interpreterOpcode(Uint16 opcode) {
	 
    Uint8 b4; 

    b4 = recupererAction(opcode);   //permet de connaître l'action à effectuer, recuperer l'opcode a effectuer.
    
    Uint8 b3,b2,b1;
    
    b3=(opcode&(0x0F00)) >> 8;  //on prend les 4 bits, b3 représente X 
    b2=(opcode&(0x00F0)) >> 4;  //idem, b2 représente Y 
    b1=(opcode&(0x000F));     //on prend les 4 bits de poids faible
 
    switch(b4) {
		 
     case 0:{ 
               //Cet opcode n'est pas implémenté 
                break; 
              } 
              
    case 1:{ 
                cleanScreen();
                break; 
               } 
               
     case 2:{ 
               if( cpu.nombreSaut>0){
				   cpu.nombreSaut--;
				   cpu.programCounter = cpu.pile[cpu.nombreSaut];
			   }
                break; 
				} 
				
     case 3:{ 
				cpu.programCounter = (b3 << 8) + (b2 << 4) + b1;
				cpu.programCounter -= 2;
                break; 
				} 
				
     case 4:{ 
				cpu.pile[cpu.nombreSaut] = cpu.programCounter;
				
				if(cpu.nombreSaut<15){
					cpu.nombreSaut++;
				}
				
				cpu.programCounter = (b3 << 8) + (b2 <<4) + b1;
				cpu.programCounter -= 2;
                break; 
				} 
				
    case 5:{ 
                if(cpu.V[b3] == ((b2 << 4) + b1)){
					cpu.programCounter += 2;
				}
                break; 
               } 
               
     case 6:{ 
				if(cpu.V[b3] != ((b2 << 4) + b1)){
					cpu.programCounter += 2;
				}
                break; 
				} 
				
     case 7:{ 
				if(cpu.V[b3]==cpu.V[b2]) { 
                    cpu.programCounter+=2; 
                } 

                break; 
				} 
				
     case 8:{ 
				cpu.V[b3] = (b2 << 4) + b1;
                break; 
				} 
				
    case 9:{ 
                cpu.V[b3] += ((b2 << 4) + b1);
                break; 
               } 
               
     case 10:{ 
				cpu.V[b3] = cpu.V[b2];
                break; 
				} 
				
     case 11:{ 
				cpu.V[b3] = cpu.V[b3] | cpu.V[b2];
                break; 
				} 
				
     case 12:{ 
				cpu.V[b3] = cpu.V[b3] & cpu.V[b2];
                break; 
				} 
				
    case 13:{ 
                cpu.V[b3] = cpu.V[b3] ^ cpu.V[b2];
                break; 
               } 
               
     case 14:{ 
				if((cpu.V[b3] + cpu.V[b2]) > 255){
					cpu.V[0xF] = 1;
				}
				else{
					cpu.V[0xF] = 0;
				}
				cpu.V[b3] += cpu.V[b2];
                break; 
				} 
				
     case 15:{ 
				if((cpu.V[b2] > cpu.V[b3])){
					cpu.V[0xF] = 0;
				}
				else{
					cpu.V[0xF] = 1;
				}
				
				cpu.V[b3] -= cpu.V[b2];
                break; 
				} 
				
     case 16:{ 
				cpu.V[0xF] = (cpu.V[b3]&(0x01));
				cpu.V[b3] = (cpu.V[b3] >> 1);
                break; 
				} 
				
    case 17:{ 
                if((cpu.V[b3] > cpu.V[b2])){
					cpu.V[0xF] = 0;
				}
				else{
					cpu.V[0xF] = 1;
				}
				
				cpu.V[b3] = cpu.V[b2] - cpu.V[b3];
				
                break; 
               } 
               
     case 18:{ 
				cpu.V[0xF] = (cpu.V[b3] >> 7);
				cpu.V[b3] = (cpu.V[b3] << 1);
                break; 
				} 
				
     case 19:{ 
				if(cpu.V[b3] != cpu.V[b2]){
					cpu.programCounter += 2;
				}
                break; 
				} 
				
     case 20:{ 
				cpu.I = (b3 << 8) + (b2 << 4) + b1;
                break; 
				} 
				
    case 21:{ 
                cpu.programCounter = (b3 << 8) + (b2 << 4) + b1 + cpu.V[0];
                cpu.programCounter -= 2;
                break; 
               } 
               
     case 22:{ 
				cpu.V[b3] = (rand()) % ((b2 << 4) + b1 + 1);
                break; 
				} 
				
     case 23:{ 
				dessinerEcran(b1, b2, b3);
                break; 
				} 
				
     case 24:{ 
				
                break; 
				} 
				
    case 25:{ 
                
                break; 
               } 
               
     case 26:{ 
               cpu.V[b3] = cpu.compteurCPU;
                break; 
				} 
				
     case 27:{ 
				
                break; 
				} 
				
     case 28:{ 
				cpu.compteurCPU = cpu.V[b3];
                break; 
				} 
				
    case 29:{ 
                cpu.compteurSon = cpu.V[b3];
                break; 
               } 
               
     case 30:{ 
				if((cpu.I + cpu.V[b3]) > 0xFFF){
					cpu.V[0xF] = 1;
				}
				else{
					cpu.V[0xF] = 0;
				}
				cpu.I += cpu.V[b3];
				
                break; 
				} 
				
     case 31:{ 
				cpu.I = cpu.V[b3] * 5;
                break; 
				} 
				
     case 32:{ 
				cpu.memoire[cpu.I] = (cpu.V[b3]-cpu.V[b3]%100)/100; //stocke les centaines
				cpu.memoire[cpu.I+1] = (cpu.V[b3]-cpu.V[b3]%10)/10; //stocke les dizaines
				cpu.memoire[cpu.I+2] = cpu.V[b3]-cpu.memoire[cpu.I]*100-10*cpu.memoire[cpu.I+1];//les unités
                break; 
				} 
				
    case 33:{ 
                Uint8 i=0;
                
                for(i = 0; i<=b3; i++){
					cpu.memoire[cpu.I+i]=cpu.V[i];
				}
                break; 
               } 
               
     case 34:{ 
				 Uint8 i=0;
                
                for(i = 0; i<=b3; i++){
					cpu.V[i]=cpu.memoire[cpu.I+i];
				}
                break; 
				}    
				
	 default:{
				break;
				}
				
}
	cpu.programCounter+=2;  //prochain opcodes, +2 car les adresse mémoire sont en 8 bit et l'opcode en 16.
}

void dessinerEcran(Uint8 b1,Uint8 b2, Uint8 b3) { 
    Uint8 x=0,y=0,k=0,codage=0,j=0,decalage=0; 
    cpu.V[0xF]=0; 

     for(k=0;k<b1;k++) { 
            codage=cpu.memoire[cpu.I+k];//on récupère le codage de la ligne à dessiner 

            y=(cpu.V[b2]+k)%WIDTH_CHIP8;//on calcule l'ordonnée de la ligne à dessiner, on ne doit pas dépasser WIDTH_CHIP8

            for(j=0,decalage=7;j<8;j++,decalage--) { 
                x=(cpu.V[b3]+j)%HEIGHT_CHIP8; //on calcule l'abscisse, on ne doit pas dépasser HEIGHT_CHIP8

                        if(((codage)&(0x1<<decalage))!=0) {   			//si c'est blanc  //on récupère le bit correspondant
                            if( pixel[x][y].color==WHITE) { 			//le pixel était blanc
                                pixel[x][y].color=BLACK;		//on l'éteint 
                                cpu.V[0xF]=1; 		//il y a donc collusion 

                            } 
                            else { //sinon
                                 pixel[x][y].color=WHITE;//on l'allume 
                            } 


                        } 

            } 
        } 

}

