#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED
#include "structure.h"

locations lire_location();

void affiche_location(locations loc);

void lire_tab_locations(locations *tab_loc,int *n);

void affiche_tab_locations(locations *tab_loc,int n);

int rechercher_location(locations *tab_loc,int n);

void  Modifier_location(locations *loc);

void supprimer_location(locations *tab_loc, int *n,int pos);

int  comparer_date(Date dt1,Date dt2);

int verifier(char s[]);

int reponse_menu(int max_menu);

int entier_taille_fixe(int taille_min_int, int taille_max_int);
#endif // LOCATION_H_INCLUDED
