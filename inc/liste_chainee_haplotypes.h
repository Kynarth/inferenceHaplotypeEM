#ifndef H_LISTE_CHAINEE_HAPLOTYPES
#define H_LISTE_CHAINEE_HAPLOTYPES

/* fonctions.h */
#include "../inc/generation_haplotypes.h"

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

/* variables globales ======================================================================== */

/* constantes ================================================================================ */

/* structures ================================================================================ */

typedef struct TypeGeno
{
    TypeGenoBase base;
    int idHaploCompl;
    int nbIndGeno;
    int proba;
    struct TypeGeno* next;
}TypeGeno;

typedef TypeGeno* TGeno;

typedef struct TypeHaplo
{
    TypeHaploBase base;
    int freq;
    TGeno teteGeno;
    struct TypeHaplo* next;
}TypeHaplo;

typedef TypeHaplo* THaplo;

typedef struct TypePaireHaplo
{
    int idHaplo1;
    int idHaplo2;
}TypePaireHaplo;

/* fonctions privée ========================================================================== */
void creation_liste(TypeHaploBase* listeHaplo, TypeGenoBase* listeGeno, int nbHaploNonRedondant);
int recherche_haplo_complementaire(TypeHaploBase haploRef, TypeGenoBase geno);

/* point d'entree ============================================================================ */


#endif /* H_LISTE_CHAINEE_HAPLOTYPES */
