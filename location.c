#include "structure.h"
#include "location.h"
#include "appartement.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

Date saisir_date()
{
    Date dt;
    printf("l\'annee:\n");
    dt.annee = entier_taille_fixe(4, 5);
    do
    {
        printf("le mois:\n");
        dt.mois = entier_taille_fixe(1, 2);
    } while (dt.mois > 12 || dt.mois < 1);
    if (dt.annee % 4 == 0)
    {
        if (dt.mois == 1 || dt.mois == 3 || dt.mois == 5 || dt.mois == 7 || dt.mois == 8 || dt.mois == 10 || dt.mois == 12)
        {
            do
            {
                printf("le jour:\n");
                dt.jour = entier_taille_fixe(1, 2);
            } while (dt.jour < 1 || dt.jour > 31);
        }
        else if (dt.mois == 2)
        {
            do
            {
                printf("le jour:\n");
                dt.jour = entier_taille_fixe(1, 2);
            } while (dt.jour < 1 || dt.jour > 28);
        }
        else
        {
            do
            {
                printf("le jour:\n");
                dt.jour = entier_taille_fixe(1, 2);
            } while (dt.jour < 1 || dt.jour > 30);
        }
    }
    else
    {

        if (dt.mois == 1 || dt.mois == 3 || dt.mois == 5 || dt.mois == 7 || dt.mois == 8 || dt.mois == 10 || dt.mois == 12)
        {
            do
            {
                printf("le jour:\n");
                dt.jour = entier_taille_fixe(1, 2);
            } while (dt.jour < 1 || dt.jour > 31);
        }
        else
        {
            do
            {
                printf("le jour:\n");
                dt.jour = entier_taille_fixe(1, 2);
            } while (dt.jour < 1 || dt.jour > 30);
        }
    }
    return dt;
}

int comparer_date(Date dt1, Date dt2) //date1 inferieure a date2
{
    if (dt1.annee < dt2.annee)
        return 1;
    else if (dt1.annee > dt2.annee)
        return 0;
    else
    {
        if (dt1.mois < dt2.mois)
            return 1;
        else if (dt1.mois > dt2.mois)
            return 0;
        else
        {
            if (dt1.jour < dt2.jour)
                return 1;
            else
                return 0;
        }
    }
}

locations lire_location()
{
    Date current_time;
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    locations loc;
    int i;
    printf("donner le nom\n");
    fflush(stdin);
    fgets(loc.nom, 20, stdin);
    current_time.annee = instant.tm_year + 1900;
    current_time.mois = instant.tm_mon + 1;
    current_time.jour = instant.tm_mday;
    do
    {
        do
        {
            printf("donner la date de debut\n");
            loc.dloc = saisir_date();
        } while (comparer_date(loc.dloc, current_time) == 1);
        printf("donner la date de fin\n");
        loc.floc = saisir_date();
    } while (comparer_date(loc.floc, loc.dloc) == 1);
    printf("choisissez un appartement\n");

    loc.apr = lire_appartement(); /////////////// twalli bel Id kahaw /////////
    return (loc);
}

void affiche_location(locations loc)
{
    printf("le nom est:%s\n", loc.nom);
    printf("la date de debut est:%d\\%d\\%d\n", loc.dloc.jour, loc.dloc.mois, loc.dloc.annee);
    printf("la date de fin est:%d\\%d\\%d\n", loc.floc.jour, loc.floc.mois, loc.floc.annee);
    printf("l\'appartement a lou%ce est:\n", 130);
    affiche_appartement(loc.apr);
}

void lire_tab_locations(locations *tab_loc, int *n)
{
    int k, t = 0, i;
    locations loc;
    do
    {
        while (1)
        {
            printf("inserez une novelle location\n");
            loc = lire_location();
            for (i = 0; i < *n; i++)
                if (tab_loc[i].apr.id == loc.apr.id && comparer_date(loc.dloc, tab_loc[i].floc))
                    t = 1;
            if (t == 0)
                break;
        }
        tab_loc[*n] = loc;
        (*n)++;
        printf("voulez vous inserer une nouvelle location ?\noui:1  non:0");
        k = reponse_menu(1);
    } while (k == 1);
}

void affiche_tab_locations(locations *tab_loc, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("location num%cro %d :\n", 130, i + 1);
        affiche_location(tab_loc[i]);
    }
}

int rechercher_location(locations *tab_loc, int n)
{
    char nom[30];
    int i;
    printf("la location a chercher:\n", 130);
    printf("nom:\n");
    fgets(nom, 30, stdin);
    for (i = 0; i < n; i++)
    {
        if (strcmp(tab_loc[i].nom, nom) == 0)
            return i;
    }
    return -1;
}

void Modifier_location(locations *loc)
{
    int i, j;
    printf("1-modifier l\'appartement de la location\n");
    printf("2-modifier la date de la location\n");
    printf("0-annuler\n");
    i = reponse_menu(2);
    switch (j)
    {
    case 1:
    {
        printf("introduire le nouveau identifiant\n");
        loc->apr.id = entier_taille_fixe(0,8);
        break;
    }
    case 2:
    {
        printf("donner la nouvelle date de debut");
        printf("le jour:\n");
        loc->dloc.jour = entier_taille_fixe(1, 2);
        printf("le mois:\n");
        loc->dloc.mois = entier_taille_fixe(1, 2);
        printf("l\'annee:\n");
        loc->dloc.annee = entier_taille_fixe(4, 4);
        printf("donner la nouvelle date de fin");
        printf("le jour:\n");
        loc->floc.jour = entier_taille_fixe(4, 4);
        printf("le mois:\n");
        loc->floc.mois = entier_taille_fixe(1, 2);
        printf("l\'annee:\n");
        loc->floc.annee = entier_taille_fixe(1, 2);
        break;
    }
    case 0:
    {
        break;
    }
    }
}

void supprimer_location(locations *tab_loc, int *nloc, int pos)
{
    int i;
    for (i = pos; i < (*nloc) - 1; i++)
    {
        tab_loc[i] = tab_loc[i + 1];
        (*nloc) -= 1;
    }
}

int verifier(char s[])
{
    int t = 1, i;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (((s[i] >= 'a') && (s[i] <= 'z')) || ((s[i] >= 'A') && (s[i] <= 'Z')))
            t = -1;
    }
    return t;
}

int reponse_menu(int max_menu)
{
    char re[30];
    int RE;
    do
    {
        Color(14, 0);
        fflush(stdin);
        printf("\nVotre choix: ");
        fgets(re, 30, stdin);
        re[strlen(re) - 1] = '\0';
        fflush(stdin);
    } while (strlen(re) != 1 || verifier(re) == -1 || atoi(re) > max_menu);
    RE = atoi(re);
    return RE;
}

int entier_taille_fixe(int taille_min_int, int taille_max_int)
{
    char re[30];
    int RE;
    do
    {
        Color(14, 0);
        printf("--->: ");
        fgets(re, 30, stdin);
    } while (((strlen(re) > taille_max_int) && (strlen(re) < taille_min_int)) || verifier(re) == -1);
    RE = atoi(re);
    return RE;
}