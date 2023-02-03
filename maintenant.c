#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//fonction du TD7
typedef int Element;

typedef struct ligne{
	long int ID;

    double tmin;
	double tmax;

    double tsomme;
	double tnbr;

}Ligne;

typedef struct arb {
	Ligne* station ;
	struct arb* fg;
	struct arb* fd;
	int equilibre;
	int Hauteur;
}Arbre;

typedef Arbre* PArbre;

typedef struct{
	int elmt;
	int info;
}TArbBin;

Ligne* creationLigne(long int id, double max, double min, double somme, double nbr){
	Ligne* nouveau = malloc(sizeof(Ligne));
	nouveau->ID = id;
	nouveau->tmin = min;
	nouveau->tmax = max;
    nouveau->tsomme = somme;
    nouveau->tsomme = nbr;
	return nouveau;
}

Arbre* creationArbre(long int id, double max, double min, double somme, double nbr){
	Arbre* nouveau = malloc(sizeof(Arbre));
	nouveau->fg = NULL;
	nouveau->fd = NULL;
	nouveau->station = creationLigne(id,max,min, somme, nbr);
	nouveau->equilibre = 0 ;
	return nouveau;
}



void infixeInt(Arbre* a){
	if(a!=NULL){
		infixeInt(a->fg);
		printf("ID : %ld", a->station->ID);
		printf("\n");
		printf("tmax : %lf", a->station->tmax);
		printf("\n");
		printf("tmin : %lf", a->station->tmin);
		printf("\n");
        printf("tmoyenne : %lf", a->station->tsomme / a->station->tnbr);
		infixeInt(a->fd);
	}
}
/*
void infixeFloat(Arbre* a){
	if(a!=NULL){
		infixeFloat(a->fg);
		printf("%f", a->station->ID);
		infixeFloat(a->fd);
	}
}
/*
* info = 1 si equilibre et 0 si hauteur
*/
int maxInt(int a, int b) {
	return (a<b ? b : a);
}
int minInt(int a, int b) {
	return (a<b ? a : b);
}

int max3Int(int a, int b, int c){
	int z = maxInt( a, b);
	return maxInt(z, c);
}

int min3Int(int a, int b, int c){
	int z = minInt( a, b);
	return minInt(z, c);
}

int maxfloat(double a, double b) {
	return (a<b ? b : a);
}
int minfloat(double a, double b) {
	return (a<b ? a : b);
}

int max3float( double a, double b, double c){
	double z = maxfloat( a, b);
	return maxfloat(z, c);
}

int min3float(double a, double b, double c){
	double z = minfloat( a, b);
	return minfloat(z, c);
}

int estVide(Arbre* a) {

return(a == NULL ? 1:0);}

PArbre filsGauche(PArbre a) {
	return a->fg;
}

PArbre filsDroit(PArbre a) {
	return a->fd;
}

/*
* -1 si vide
* 0 si feuille
* 1+ max de la hauteur des sous-arbres
*/
int hauteur(Arbre* a) {
	if (estVide(a) == 1){ return -1;}
	return 1 + maxInt(hauteur(filsGauche(a)), hauteur(filsDroit(a)));}

/*
Arbre* insertABR(Arbre* a, int e){
	
	if(a == NULL){
		Arbre* nouveau = creationArbre(e);
		return nouveau;
	}
		if(a->elmt == e){
			return a;
		}
		if(e > a->elmt){
			if(a->fd == NULL && a->fg == NULL){
				Arbre* nouveau = creationArbre(e);
				a->fg = nouveau;
				return a;
			}
			else{
				a->fd = insertABR(a->fd, e);
			}
		}
		if(e < a->elmt){
			if(a->fd == NULL && a->fg == NULL){
				Arbre* nouveau = creationArbre(e);
				a->fd = nouveau;
				return a;
			}
			else{
				a->fg = insertABR(a->fg, e);
			}
		}
	return a;
}

*/

Arbre* rotationGauche(Arbre* a){

	Arbre* pivot = a->fd;
	int eq_a;
	int eq_p;
	a->fd = pivot->fg;
	pivot->fg = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - maxInt(eq_p, 0) - 1;
	pivot->equilibre = min3Int( eq_p-2, eq_a+eq_p-2, eq_p-1);
	a = pivot;
	return pivot;
}


Arbre* rotationDroite(Arbre* a){
	Arbre* pivot = a->fg;
	int eq_a;
	int eq_p;
	a->fg = pivot->fd;
	pivot->fd = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a - minInt(eq_p, 0) + 1;
	pivot->equilibre = max3Int( eq_p+2, eq_a+eq_p+2, eq_p+1);
	a = pivot;
	return a;
}

Arbre* doubleRotationGauche( Arbre* a){
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}
Arbre* doubleRotationDroite( Arbre* a){
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}

Arbre* equilibrerAVL( Arbre* a){

	if(a->equilibre >= 2){
		if(a->fd != NULL){
			if(a->fd->equilibre >= 0){
				return rotationGauche(a);}
			else{
				return doubleRotationGauche(a);
			}
		}
	}
	else if(a->equilibre <= -2){
		if(a->fg != NULL){
			if(a->fg->equilibre <= 0){
				return rotationDroite(a);
			}
			else{
				return doubleRotationDroite(a);
			}
		}
	}
	return a;
}


Arbre* insertE( Arbre* a, long int id, double temp, int* h, char choix){
	if (choix == 'i'){
		long int e = id;
		if(a == NULL){
			*h=1;
			a= creationArbre(id,temp,temp,temp,1);
			//printf("je suis là %ld \n", a->station->ID);
			return a;
		}
		else if( e< a->station->ID){
			a->fg = insertE(a->fg,id,temp, h, 'i');
			*h = -*h;
		}
		else if(e > a->station->ID){
			a->fd = insertE(a->fd, id,temp, h, 'i');
		}
		else{
			*h = 0;
			a->station->tmin = minfloat(temp, a->station->tmin);
			a->station->tmax = maxfloat(temp, a->station->tmax);
            a->station->tsomme = a->station->tsomme + temp;
            a->station->tnbr += 1;
			return a;
		}

		if(*h != 0){
			a->equilibre = a->equilibre+ *h;
			a = equilibrerAVL(a);
			if(a->equilibre == 0){
				*h = 0;
			}
			else{
				*h=1;
			}
		}
		return a;
	}
	else return a;
}
void InfixeSysteme(Arbre * a, FILE* fichier/*, int b*/){
     //croissant
    if(a!=NULL){
        double c;
		InfixeSysteme(a->fg, fichier/*, b+1*/);
        //fprintf(fichier, "%d ", b);
        fprintf(fichier, "%ld ", a->station->ID);
        fprintf(fichier, "%lf ", a->station->tmax);
        fprintf(fichier, "%lf ", a->station->tmin);
        c = a->station->tsomme / a->station->tnbr;
        fprintf(fichier, "%lf\n", c);
       	InfixeSysteme(a->fd, fichier/*,b+1*/ );
    }
}

void infixeDat(Arbre* a, char* DAT){
    //croissant
    FILE* fichier = NULL;
	fichier = fopen(DAT, "w");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	else if(a!=NULL){
        InfixeSysteme(a, fichier/*, 1*/);
    }
    else{
        printf("Arbre NULL");
    }
    fclose(fichier);
}
void InfixeSystemeD(Arbre * a, FILE* fichier/*, int b*/){
    //décroissant
    if(a!=NULL){
        double c;
		InfixeSystemeD(a->fd, fichier/*,b+1*/ );
        //fprintf(fichier, "%d ", b);
        fprintf(fichier, "%ld ", a->station->ID);
        fprintf(fichier, "%lf ", a->station->tmax);
        fprintf(fichier, "%lf ", a->station->tmin);
        c = a->station->tsomme / a->station->tnbr;
        fprintf(fichier, "%lf\n", c);
        InfixeSystemeD(a->fg, fichier/*, b+1*/);
    }
}

void infixeDatD(Arbre* a, char* DAT){
    //décroissant
    FILE* fichier = NULL;
	fichier = fopen(DAT, "w");
	if(fichier == NULL) {
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	else if(a!=NULL){
        InfixeSystemeD(a, fichier/*, 1*/);
    }
    else{
        printf("Arbre NULL");
    }
    fclose(fichier);
}

int pression1(char* CSV,char*DAT, int croissant, int trieur){
    //AVL ssi trieur == 1
    //croissant ssi == 1
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

int main (int argc, char *argv[])
{
    
    int sortie = 0;
    int choix = 1;
    int croissant = 1;
    
    for(int i =1; i<4; i++){
        if(strcmp(argv[i], "0") == 0){
            croissant = 0;
        }
    }
    
    if(strcmp(argv[1], "pressporaire2.csv") == 0){
        pression1(argv[1], argv[2], croissant, choix);
    }
    if(strcmp(argv[1], "temporaire2.csv") == 0){
        temperature1(argv[1], argv[2], croissant, choix);
    }


    return sortie;
}
