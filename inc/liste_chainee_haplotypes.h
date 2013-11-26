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

/* Rempli le tableau de genotypes non redondants */
typedef struct TypeGeno
{
    int idHaploCompl;
    int nbIndGeno;
    int proba;
}TypeGeno;

typedef TypeGeno* TGeno;

/* Rempli les listes chainees de genotypes expliques par les haplotypes */
typedef struct TypeGenoExplique
{
    TypeGenoBase base;
    int idHaploCompl;
    int nbIndGeno;
    int proba;
    TGenoExp next;
}TypeGenoExplique;

typedef TypeGenoExplique* TGenoExp;

/* Rempli le tableau de haplotypes non redondants */
typedef struct TypeHaplo
{
    int id;
    float freq;
    int* haplotype;
    TGenoExp teteGeno;
}TypeHaplo;

typedef TypeHaplo* THaplo;

/* Rempli les listes chainees de paires d'haplotypes expliquant les genotypes */ 
typedef struct TypePaireHaplo
{
    int idHaplo1;
    int idHaplo2;
}TypePaireHaplo;

/* fonctions privée ========================================================================== */
/*void creation_liste(TypeHaploBase* listeHaplo, TypeGenoBase* listeGeno, int nbHaploNonRedondant);*/
int recherche_haplo_complementaire(TypeHaploBase haploRef, TypeGenoBase geno);

/* point d'entree ============================================================================ */


#endif /* H_LISTE_CHAINEE_HAPLOTYPES */
