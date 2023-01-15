#include <stdio.h>
#include <stdlib.h>
#include "appartement.h"
#include "location.h"
#include "structure.h"
#include <unistd.h>
#include <time.h>

#include <string.h>

time_t secondes;
struct tm instant;

int main()
{

    time(&secondes);
    instant = *localtime(&secondes);
    appart apr, tab_apr[30];
    int result = 0, N = 0, pos, i = 0, rep, a, j, t = 1, N_apr = 0, N_loc = 0;
    locations tab_loc[30], loc;
    char ch[30], pass[30], nu[20];
    //Mod de Passe
    do
    {
        Color(14, 0);
        printf("\t\t\t\tNOM D\'UTILISATEUR:\n\t\t\t\t");
        fgets(nu, 20, stdin);
        printf("\n\t\t\t\tMOT DE PASSE:\n\t\t\t\t");
        motDePasse(pass, 30);
        strcpy(ch, pass);
        printf("\n\t\t\t\tRetapez votre mot de passe:\n\t\t\t\t");
        motDePasse(pass, 30);
        result = strcmp(pass, ch);
        if (result != 0)
        {
            Color(4, 0);
            printf("\nVos mots de passes ne corresponde pas.\n essayez de nouveau\n");
            Color(15, 0);
        }
        else
        {
            Color(4, 0);
            printf("\n le mot de passe entree n est pas correcte veuillez saisir un autre mot de passe\n");
            Color(15, 0);
        }
    } while (strcmp(pass, "ahmedfiras") != 0);

    system("cls");
    while (1)
    {
        printf("**********************************************************************");
        printf("\n\tMenu Principale\t\n");
        printf("**********************************************************************\n");
        system("COLOR 14");
        Color(12, 0);
        printf("1) a propos les locations\n");
        printf("2) a propos les appartements\n");
        printf("0) Quitter\n");
        a = reponse_menu(2);
        printf("\n *****  %d/%d/%d   ***   %d:%d:%d ****\n", instant.tm_mday, instant.tm_mon + 1, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec);

        switch (a)
        {
        case 1: //menu locations
        {
            int m = 1;
            i = 0;
            //fichier locations
            FILE *fichier;
            fichier = fopen("locations.txt", "rt");
            if (fichier == NULL)
                printf("\n le fichier n'existe pas");
            else
            {
                while (!feof(fichier))
                {
                    fscanf(fichier, "%s %d %d %d %d %d %d %d %f %s\n", tab_loc[i].nom, &tab_loc[i].dloc.jour, &tab_loc[i].dloc.mois, &tab_loc[i].dloc.annee, &tab_loc[i].floc.jour, &tab_loc[i].floc.mois, &tab_loc[i].floc.annee, &tab_loc[i].apr.id, &tab_loc[i].apr.surface, tab_loc[i].apr.description);
                    i++;
                }
                N_loc = i;
            }
            fclose(fichier);
            //fichier locations
            system("cls");
            while (m)
            {
                Color(13, 0);
                printf("**********************************************************************");
                printf("\n\tGestion Des Locations\t\n");
                printf("**********************************************************************\n");
                printf("1) Saisir une location\n");
                printf("2) Saisir un ensemble des locations \n");
                printf("3) Afficher l'ensemble des locations \n");
                printf("4) Rechercher une location\n");
                printf("5) Modifier une location\n");
                printf("6) Supprimer une location\n");
                printf("0) Quitter\n");
                printf("\n *****  %d/%d/%d   ***   %d:%d:%d ****\n", instant.tm_mday, instant.tm_mon + 1, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec);
                printf("donner un entier entre 0 et 6 \n");
                i = reponse_menu(6);
                switch (i)
                {
                case 1: //lire location
                {
                    system("cls");
                    while (1)
                    {
                        printf("les appartements disponibles");
                        affiche_tab_appartement(tab_apr, N_apr);
                        printf("Saisir une location\n");
                        loc = lire_location();
                        for (i = 0; i < N_loc; i++)
                        {
                            if (tab_loc[i].apr.id == loc.apr.id)
                            {
                                if ((comparer_date(tab_loc[i].dloc, loc.floc) && comparer_date(loc.dloc, tab_loc[i].dloc)) || (comparer_date(tab_loc[i].floc, loc.floc) && comparer_date(loc.floc, tab_loc[i].floc)))
                                {
                                    t = 0;
                                    printf("Chevauchement de date!");
                                }
                            }
                        }
                        if (t == 1)
                            break;
                    }
                    tab_loc[N_loc] = loc;
                    N_loc++;
                    system("cls");
                    break;
                }
                case 2: //lire tab locations
                {
                    lire_tab_locations(tab_loc, &N_loc);
                    system("cls");
                    break;
                }
                case 3: //afficher tab locations
                {
                    affiche_tab_locations(tab_loc, N_loc);
                    break;
                }
                case 4: //rechercher locatioon
                {
                    pos = rechercher_location(tab_loc, N_loc);
                    if (pos == -1)
                        printf("la location n existe pas\n", 130);
                    else
                        affiche_location(tab_loc[pos]);
                    break;
                }
                case 5: //modifier locarion
                {
                    printf("donner la location a modifier\n", 130);
                    pos = rechercher_location(tab_loc, N_loc);
                    if (pos == -1)
                        printf("la location n\'%cxiste pas\n", 130, 130);
                    else
                    {
                        affiche_location(tab_loc[pos]);
                        printf("voues etes sure de vouloir modifier cette location\n 0-non 1-oui\n");
                        rep = reponse_menu(1);
                        if (rep == 1)
                        {
                            Modifier_location(&tab_loc[pos]);
                            affiche_location(tab_loc[pos]);
                        }
                        else
                            printf("modification annulee");
                    }
                    break;
                }
                case 6: //supprimer location
                {
                    printf("donner la location a supprimer\n", 130);
                    pos = rechercher_location(tab_loc, N_loc);
                    if (pos == -1)
                        printf("la location n\'%cxiste pas\n", 130, 130);
                    else
                    {
                        affiche_location(tab_loc[pos]);
                        printf("vous etes sure de vouloir supprimer cette location\n 0-non 1-oui\n");
                        rep = reponse_menu(1);
                        if (rep == 1)
                        {
                            supprimer_location(tab_loc, &N_loc, pos);
                            affiche_tab_locations(tab_loc, N_loc);
                        }
                        else
                            printf("suppression annul%ce\n", 130);
                    }
                    break;
                }
                case 0:
                {
                    //fichier locations
                    fichier = fopen("locations.txt", "wt");
                    if (fichier == NULL)
                        printf("\n le fichier n'existe pas");
                    else
                    {
                        for (i = 0; i < N_loc; i++)
                        {
                            fprintf(fichier, "%s %d %d %d %d %d %d %d %f %s\n", tab_loc[i].nom, &tab_loc[i].dloc.jour, &tab_loc[i].dloc.mois, &tab_loc[i].dloc.annee, &tab_loc[i].floc.jour, &tab_loc[i].floc.mois, &tab_loc[i].floc.annee, &tab_loc[i].apr.id, &tab_loc[i].apr.surface, tab_loc[i].apr.description);
                        }
                    }
                    fclose(fichier);
                    //fichier locations
                    m = 0;
                    system("cls");
                    break;
                }
                }
            }
            break;
        }
        case 2: //menu appartment
        {
            system("COLOR 514");
            Color(14, 5);
            int m = 1;
            i = 0;
            //fichier appartement
            FILE *fichier;
            fichier = fopen("appartement.txt", "rt");
            if (fichier == NULL)
                printf("\n le fichier n'existe pas");
            else
            {
                while (!feof(fichier))
                {
                    fscanf(fichier, "%d %f %s\n", &tab_apr[i].id, &tab_apr[i].surface, tab_apr[i].description);
                    i++;
                }
                N_apr = i;
            }
            fclose(fichier);
            //fichier appartement
            system("cls");
            while (m)
            {
                printf("**********************************************************************");
                printf("\n\tGestion Des Appartement\t\n");
                printf("**********************************************************************\n");
                printf("1) Saisir un appartement\n");
                printf("2) Saisir un ensemble des appartements \n");
                printf("3) Afficher l'ensemble des appartements \n");
                printf("4) Rechercher un appartement\n");
                printf("5) Modifier un appartement\n");
                printf("6) Supprimer un appartement\n");
                printf("0) Quitter\n");
                printf("\n *****  %d/%d/%d   ***   %d:%d:%d ****\n", instant.tm_mday, instant.tm_mon + 1, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec);
                printf("Donner un entier entre 0 et 6 \n");
                j = reponse_menu(6);
                switch (j)
                {
                case 1: //lire appartement
                {
                    while (1)
                    {
                        printf("saisir un appartement\n");
                        apr = lire_appartement();
                        for (i = 0; i < N_apr; i++)
                        {
                            if (tab_apr[i].id == apr.id)
                                t = 0;
                        }
                        if (t == 0)
                            printf("Cette id existe deja\n");
                        break;
                    }
                    tab_apr[N_apr] = apr;
                    N_apr++;
                    system("cls");
                    break;
                }
                case 2: //lire tab appartement
                {
                    lire_tab_appartement(tab_apr, &N_apr);
                    system("cls");
                    break;
                }
                case 3: //affiche tab appartement
                {
                    affiche_tab_appartement(tab_apr, N_apr);
                    break;
                }
                case 4: //rechercher appartement
                {
                    pos = rechercher_appartement(tab_apr, N_apr);
                    if (pos == -1)
                        printf("l\'appartement n existe pas\n", 130);
                    else
                        affiche_appartement(tab_apr[pos]);
                    break;
                }
                case 5: //modifier appartement
                {
                    printf("donner l\'appartement a modifier\n", 130);
                    pos = rechercher_appartement(tab_apr, N_apr);
                    if (pos == -1)
                        printf("l\'appartement n\'%cxiste pas\n", 130, 130);
                    else
                    {
                        affiche_appartement(tab_apr[pos]);
                        printf("voues etes sure de vouloir modifier cette appartement\n 0-non 1-oui\n");
                        scanf("%d", &rep);
                        if (rep == 1)
                        {
                            Modifier_appartement(&tab_apr[pos]);
                            affiche_appartement(tab_apr[pos]);
                        }
                        else
                        {
                            printf("modification annulee");
                        }
                    }
                    break;
                }
                case 6: //supprimer appartement
                {
                    printf("donner l\'appartement a supprimer\n", 130);
                    pos = rechercher_appartement(tab_apr, N_apr);
                    if (pos == -1)
                        printf("l\'appartement n\'%cxiste pas\n", 130, 130);
                    else
                    {
                        affiche_appartement(tab_apr[pos]);
                        printf("vous etes sure de vouloir supprimer cette appartement\n 0-non 1-oui\n");
                        scanf("%d", &rep);
                        if (rep == 1)
                        {
                            supprimer_appartement(tab_apr, &N_apr, pos);
                            affiche_tab_appartement(tab_apr, N_apr);
                        }
                        else
                            printf("suppression annul%ce\n", 130);
                    }
                    break;
                }
                case 0:
                {
                    //fichier appartement
                    fichier = fopen("appartement.txt", "wt");
                    if (fichier == NULL)
                        printf("\n le fichier n'existe pas");
                    else
                    {
                        for (i = 0; i < N_apr; i++)
                        {
                            fprintf(fichier, "%d %f %s\n", &tab_apr[i].id, &tab_apr[i].surface, tab_apr[i].description);
                        }
                    }
                    fclose(fichier);
                    //fichier appartement
                    m = 0;
                    system("cls");
                    break;
                }
                }
            }
            break;
        }
        case 0: //exit
        {
            system("cls");
            Color(0, 7);
            printf("\n\n\n\n\t\t\tMERCI POUR CHOISIR NOS SERVICES");
            sleep(2);
            exit(1);
        }
        }
    }
    return 0;
}