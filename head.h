#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "ligne.h"
#include "arbreVL.h"


Ligne* creationLigne(long int id, double max, double min, double somme, double nbr);

Arbre* creationArbre(long int id, double max, double min, double somme, double nbr);


void infixeInt(Arbre* a);

int maxInt(int a, int b);
int minInt(int a, int b);

int max3Int(int a, int b, int c);
int min3Int(int a, int b, int c);


int maxfloat(double a, double b);
int minfloat(double a, double b);

int max3float( double a, double b, double c);

int min3float(double a, double b, double c);

int estVide(Arbre* a);

Arbre* filsGauche(Arbre* a);
Arbre* filsDroit(Arbre* a);

int hauteur(Arbre* a);


Arbre* rotationGauche(Arbre* a);
Arbre* rotationDroite(Arbre* a);

Arbre* doubleRotationGauche( Arbre* a);
Arbre* doubleRotationDroite( Arbre* a);

Arbre* equilibrerAVL( Arbre* a);

Arbre* insertE( Arbre* a, long int id, double temp, int* h, char choix);

void InfixeSysteme(Arbre * a, FILE* fichier/*, int b*/);
void infixeDat(Arbre* a, char* DAT);

void InfixeSystemeD(Arbre * a, FILE* fichier/*, int b*/);
void infixeDatD(Arbre* a, char* DAT);



int pression1(char* CSV,char*DAT, int croissant, int trieur);


int temperature1(char* CSV, char* DAT, int croissant, int trieur);

int main (int argc, char *argv[]);
