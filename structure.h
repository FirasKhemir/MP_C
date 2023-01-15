#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef struct dt
{
    int jour;
    int mois;
    int annee;
}Date;

typedef struct appartement
{
    int id;
    float surface;
    char description[30];
}appart;

typedef struct loc
{
    char nom[20];
    Date dloc;
    Date floc;
    appart apr;
}locations;

#endif // STRUCTURE_H_INCLUDED
