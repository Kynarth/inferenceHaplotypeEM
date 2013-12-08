#ifndef H_INFERENCE_HAPLOTYPE_EM
#define H_INFERENCE_HAPLOTYPE_EM

/* inference_haplotype_EM.h */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

#include "../inc/generation_haplotypes.h"
#include "../inc/liste_doublement_chainee.h"

/* point d'entree =============================================================================== */

 void inference_haplotype_em(double seuil, int nbGeno, int nbHaplo, int nbEtapeMax,
                             double** tabFreq, TypeGeno** tabGeno, TypeHaplo** tabHaplo);
                             
                             
#endif /* H_INFERENCE_HAPLOTYPE_EM */
