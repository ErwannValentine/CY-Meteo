#include "head.h"
//remplie les variables d'une structure Ligne
Ligne* creationLigne(long int id, double max, double min, double somme, double nbr){
	Ligne* nouveau = malloc(sizeof(Ligne));
	nouveau->ID = id;
	nouveau->tmin = min;
	nouveau->tmax = max;
    nouveau->tsomme = somme;
    nouveau->tsomme = nbr;
	return nouveau;
}

//remplie les variables d'une structure Arbre
Arbre* creationArbre(long int id, double max, double min, double somme, double nbr){
	Arbre* nouveau = malloc(sizeof(Arbre));
	nouveau->fg = NULL;
	nouveau->fd = NULL;
	nouveau->station = creationLigne(id,max,min, somme, nbr);
	nouveau->equilibre = 0 ;
	return nouveau;
}

