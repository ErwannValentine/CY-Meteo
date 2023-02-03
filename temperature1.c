#include "head.h"


int temperature1(char* CSV, char* DAT, int croissant, int trieur){
    Arbre* a;;
	int h;
	h=0;
    //
    FILE* fic ;
    char ligne[81];
    char *ptr_chaine ; // pointeur pour balayer les sous-chaines obtenues
    long int num_ligne = 1 ;
    long int data_entier;
    double data_reel;
//----------------------- ouverture du fichier de données CSV ------------------------------
    fic = fopen( CSV, "rt") ;
    if (fic==NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
//----------------------- lecture du fichier de données CSV ------------------------------
// on lit une ligne après l'autre jusqu'à  la fin du fichier
    while ( fgets( ligne, 81, fic) != NULL )
    {
        //printf("\n Ligne %2ld :", num_ligne );
        num_ligne++ ;
        ptr_chaine = strtok (ligne, ";"); // appel d'initialisation de strtok. Séparateur = ';'
        // on lit une cellule (colonne) après l'autre jusqu'à la fin de la ligne. Notez que si les cellules contenaient
        //des données de même type, on pourrait écrire une boucle while(ptr_chaine!=NULL){}

        if (sscanf(ptr_chaine,"%ld", &data_entier) != 1)
        {
            puts("\nPb de lecture cellule 2 (entier)!");
            //printf("\n Ligne %2ld :", data_entier );
            //data_entier=-11111;
        }
        ptr_chaine = strtok (NULL, ";"); // remplace le prochain séparateur trouvé par 0
        if (sscanf(ptr_chaine,"%lf", &data_reel) != 1)
        {
            puts("\nPb de lecture cellule 4 (reel)!");
            printf("\n num station : %2ld :", data_entier );
            printf("\n\t cellule 4 (reel) : %11.3lf", data_reel);
            data_reel=-11111.111;
        }
        ptr_chaine = strtok (NULL, ";"); // non indispensable ici
// affichages :
        //printf("\n\t cellule 2 (entier): %11ld", data_entier);
        //printf("\n\t cellule 4 (reel) : %11.3lf", data_reel);
       if(trieur == 1){
            a=insertE(a,data_entier,data_reel,&h,'i');
        }
    }
    fclose(fic);
    if(croissant == 1 && trieur == 1){
        infixeDat(a, DAT);
    }
    if(croissant == 0 && trieur == 1){
        infixeDatD(a, DAT);
    }
    return 0;
}


