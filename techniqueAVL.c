#include "head.h"

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

Arbre* filsGauche(Arbre* a) {
	return a->fg;
}

Arbre* filsDroit(Arbre* a) {
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


