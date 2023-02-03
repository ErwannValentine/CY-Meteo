#include "head.h"

//parcours infixe pour afficher le contenu de l'arbre
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

//réalise une rotation gauche (cf cours)
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

//réalise une rotation droite (cf cours)
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

//réalise une double rotation gauche (cf cours)
Arbre* doubleRotationGauche( Arbre* a){
	a->fd = rotationDroite(a->fd);
	return rotationGauche(a);
}
//réalise une double rotation droite cf cours
Arbre* doubleRotationDroite( Arbre* a){
	a->fg = rotationGauche(a->fg);
	return rotationDroite(a);
}

//détermine quelles rotations sont à effectuer pour équilibrer l'AVL (cf cours)
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

//permet d'insérer un nouvel élément à l'AVL
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

//réalise un parcours infixe pour remplir un fichier dat
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


/*
pointeur de type void* passé en parametre d'une procédure checkPtr(void* p)
if NULL alors printf + exit propre valeur diff de 0

dans le script on verifie que le retour du C est correct (==0)
*/

//prépare le fichier à remplir avec InfixeSysteme
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
        printf("Arbre NULLooooooooooooo");
    }
    fclose(fichier);
}


// idem que pour InfixeSysteme, en infixe "inversé"
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

//prépare le fichier à remplir avec InfixeSystemeD
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

