#ifndef APPARTEMENT_H_INCLUDED
#define APPARTEMENT_H_INCLUDED
#include "structure.h"

char motDePasse(char *pass, int taillePass);

void Color(int couleurDuTexte,int couleurDeFond);

int verif_entier(int a);

appart lire_appartement();

void affiche_appartement(appart apr);

void lire_tab_appartement(appart *tab_appart,int *n);

void affiche_tab_appartement(appart *tab_apr,int n);

int rechercher_appartement(appart *tab_apr,int n);

void Modifier_appartement(appart *tab_apr);

void supprimer_appartement(appart *tab_apr, int *n,int pos);

#endif // APPARTEMENT_H_INCLUDED
