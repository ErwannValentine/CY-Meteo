#include "head.h"

//prend fichier.csv et autre_fichier.dat et (0 ou bien 1) en entrée, remplis le fichier dat et fait état des erreurs en sortie
int main (int argc, char *argv[])
{
    
    int sortie = 0;
    int choix = 1;// AVL =1 (choix par defaut)
    int croissant = 1; //1: trie croissant, 0: trie décroissant
    
		if(strcmp(argv[3], "0") == 0){//détermine si le trie que l'on souhaite
        	croissant = 0;
		}
    
            
    if(strcmp(argv[1], "pressporaire2.csv") == 0){
        pression1(argv[1], argv[2],croissant, choix);//prépare le fichier .dat pour la pression en mode 1
	}
    if(strcmp(argv[1], "temporaire2.csv") == 0){
        temperature1(argv[1], argv[2], croissant, choix);//prépare le fichier .dat pour la température en mode 1
    }


    return sortie;
}
