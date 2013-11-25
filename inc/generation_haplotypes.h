#ifndef H_GENERATION_HAPLOTYPES
#define H_GENERATION_HAPLOTYPES

/* fonctions.h */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

/* variables globales ======================================================================== */

int nbIndiv;
int tailleGeno;

/* constantes ================================================================================ */

#define PARAM "./fichiers/parametres.txt"
#define TAILLE_GENO tailleGeno /* longueur du fragment d'ADN observe */
#define NB_INDIV nbIndiv /* nombre d'individus sur lesquels les genotypes seront observe */

/* structures ================================================================================ */
typedef struct TypeHaploBase
{
    int id;
    int* haplotype;
    int doublon;
}TypeHaploBase;

typedef struct TypeGenoBase
{
    int id;
    int* genotype;
    int nbIdentique;
    int nbLociAmbigu;
    int nbHaplo;
    TypeHaploBase* matriceHaplo;
}TypeGenoBase;

/* fonctions privée ========================================================================== */
int lire(char* chaine, int longueur, FILE* fichier);
int initialisation_geno(TypeGenoBase* geno, int id);
void recherche_genotype_doublon(TypeGenoBase* geno1, TypeGenoBase* geno2);
void recherche_haplotyple_doublon(TypeGenoBase* geno1, TypeGenoBase* geno2);
int calcul_nb_haplo_non_redondant(TypeGenoBase* geno);
void affichage_genotype(TypeGenoBase geno);
void affichage_haplotype(TypeHaploBase haplo);


/* point d'entree ============================================================================ */


#endif /* H_GENERATION_HAPLOTYPES */
