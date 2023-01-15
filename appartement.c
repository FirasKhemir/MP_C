#include "structure.h"
#include "appartement.h"
#include "location.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define ENTER 13
#define BACKSPACE 8

char motDePasse(char *pass, int taillePass)
{
    int i = 0;
    int result = 0;

    char rep;

    do
    {
        rep = getch();
        switch (rep)
        {
        case ENTER:
            pass[i] = '\0';
            i = 0;
            break;
        case BACKSPACE:
            if (i > 0)
            {
                i--;
                printf("\b \b"); //te permet de reculer, faire un espace, reculer dans la console (efface *)
            }
            break;
        default:
            printf("*");
            pass[i] = rep;
            i++;
        }
    } while (rep != ENTER);
    return (*pass);
}

void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}

int verif_entier(int a)
{
    int i;
    char ch[30];
    itoa(a, ch, 10);
    for (i = 0; i < strlen(ch); i++)
    {
        if (ch[i] != 0 && ch[i] != 1 && ch[i] != 2 && ch[i] != 3 && ch[i] != 4 && ch[i] != 5 && ch[i] != 6 && ch[i] != 7 && ch[i] != 8 && ch[i] != 9)
            return 0;
    }
    return 1;
}

appart lire_appartement()
{
    appart apr;
    int a;
    float f;
    char s[30];
    printf("donnez l\'identifiant num%crique\n", 130);
    apr.id = entier_taille_fixe(0,8);
    printf("donnez la surface\n");
    scanf("%f",&apr.surface);
    printf("donnez la description\n");
    scanf("%s",apr.description);
    return (apr);
}

void affiche_appartement(appart apr)
{
    printf("l\'identifiant est : %d\n", apr.id);
    printf("la surface est : %f\n", apr.surface);
    printf("la description est :%s\n", apr.description);
}

void lire_tab_appartement(appart *tab_appart, int *n)
{
    int k, t = 1, i;
    do
    {
        while (1)
        {
            printf("inserez une nouvelle appartement");
            tab_appart[*n] = lire_appartement();
            for (i = 0; i < *n; i++)
            {
                if (tab_appart[i].id == tab_appart[*n].id)
                    t = 0;
            }
            if (t == 1)
                break;
        }
        (*n)++;
        printf("voulez vous inserer une nouvelle appartement ?\noui:1  non:0");
        k = reponse_menu(1);
    } while (k == 1);
}

void affiche_tab_appartement(appart *tab_apr, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("la %d eme appartement est :\n", i + 1);
        affiche_appartement(tab_apr[i]);
    }
}

int rechercher_appartement(appart *tab_apr, int n)
{
    int i, id;
    printf("l\'appartement a rechercher :\n");
    printf("id:\n");
    id = entier_taille_fixe(1,8);
    for (i = 0; i < n; i++)
    {
        if (tab_apr[i].id == id)
            return i;
    }
    return -1;
}

void Modifier_appartement(appart *tab_apr)
{
    int i, j;
    printf("1) modifier la surface de l\'appartement: \n");
    printf("2) modifier la description de l\'appartement: \n");
    printf("0) annuler\n");
    j=reponse_menu(2);
    switch (j)
    {
    case 1:
    {
        printf("introduire la nouvelle surface");
        scanf("%f",&tab_apr->surface);
        break;
    }
    case 2:
    {
        printf("donner la nouvelle Description\n");
        gets(tab_apr->description);
        break;
    }
    case 0:
        break;
    }
}

void supprimer_appartement(appart *tab_apr, int *napr, int pos)
{
    int i;
    for (i = pos; i < (*napr) - 1; i++)
    {
        tab_apr[i] = tab_apr[i + 1];
        (*napr) -= 1;
    }
}