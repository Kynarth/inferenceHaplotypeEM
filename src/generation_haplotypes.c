/* generation_haplotypes.c */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/generation_haplotypes.h"

/* fonctions tests =========================================================================== */

/* Affichage des haplytpes */
void affichage_haplotypes(TypeGeno geno)
{
    int i;
    int j;
    for(i = 0 ; i < geno.nbHaplo ; i++ )
    {
        printf("%d : ",geno.matriceHaplo[i].id);
        for(j = 0 ; j < TAILLE_GENO ; j++)
        {
           printf("%d",geno.matriceHaplo[i].haplotype[j]); 
        }
        printf("\n");
    }
}

/* Affichage des genotypes (int *) */
void affichage_genotype(TypeGeno geno)
{
    int i;
    printf("%d : ",geno.id);
    for(i = 0 ; i < TAILLE_GENO ; i++ )
    {
        printf("%d",geno.genotype[i]);
    }
    printf("\n");
}

/* Affichage des hapltypes (int *) */
void affichage_haplotype(TypeHaplo haplo)
{
    int j;
        printf("%d : ",haplo.id);
        for(j = 0 ; j < TAILLE_GENO ; j++)
        {
           printf("%d",haplo.haplotype[j]); 
        }
        printf("\n");
}

/* fonctions privees ========================================================================= */

/* Compte le nombre de loci ambigu pour un genotype donnee */
static int compte_nombre_loci_ambigu(TypeGeno geno)
{
    int i;
    int count = 0;
    for(i = 0 ; i < TAILLE_GENO ; i++ )
    {
        if(geno.genotype[i] == 1)
        {
            count++;
        }
    }
    return count;
}

/* Rempli la matrice d'haplotypes en colonne */
static void generation_haplo_possibles(TypeHaplo* matrice, int lociMax, 
                                        int countLoci, int colonne, int n)
{
    int i;
    int modulo;
    int interval;
    if (n == 2)
    {
        for( i=0 ; i < lociMax ; i++){
            matrice[i].haplotype[colonne] = 1;
        }
    }
    else if (n == 0)
    {
        for( i=0 ; i < lociMax ; i++){
            matrice[i].haplotype[colonne] = 0;
        }
    }
    else /* Lorsque le locus est ambigu */
    {
        modulo = pow(2,countLoci);
        interval = lociMax / modulo;

        for( i=0 ; i < lociMax ; i++){
            matrice[i].haplotype[colonne] = ((i/interval)%2);
        }
    } 
}

#if 0
static void affichage_haplotypes(TypeGeno geno)
{
    int i;
    int j;
    for(i = 0 ; i < geno.nbHaplo ; i++ )
    {
        printf("%d : ",geno.matriceHaplo[i].id);
        for(j = 0 ; j < TAILLE_GENO ; j++)
        {
           printf("%d",geno.matriceHaplo[i].haplotype[j]); 
        }
        printf("\n");
    }
}
#endif

/* Recherche et retourne la frequence associee a l'id d'haplotype voulu */
static double recherche_frequence_precedente(int id, double** tableauFrequence)
{
    int i = 0;
    bool_t trouve = FALSE;
    double frequencePrecedente;
    while (trouve == FALSE)
    {
        if(id == tableauFrequence[i][0])
        {
            trouve = TRUE;
            frequencePrecedente = tableauFrequence[i][2];
        }
        i++;
    }
    return frequencePrecedente;
}

/* Calcul des probabilites initiales pour chaque genotypes */
static void calculer_proba_geno(int nbGeno, TypeGeno** geno, double** tabFreq)
{
    int i;
    double freqH1, freqH2, proba, ppart;
    TypePaireHaplo* listePaireHaplo;
    for(i=0 ; i<nbGeno ; i++)
    {
        proba = 0.0;
        listePaireHaplo = geno[i]->first;
        while(listePaireHaplo != NULL)
        {
            freqH1 = recherche_frequence_precedente(listePaireHaplo->idHaplo1,tabFreq);
            freqH2 = recherche_frequence_precedente(listePaireHaplo->idHaplo2,tabFreq);
            #if 0
            printf("freqH1 : %.10f - freqH2 : %.10f -",freqH1,freqH2);
            #endif
            if(listePaireHaplo->idHaplo1 == listePaireHaplo->idHaplo2)
            {
                ppart = freqH1 * freqH1;
            }
            else
            {
                ppart = 2 * freqH1 * freqH2;
            }
            proba = proba + ppart;
            #if 0
            printf("Proba : %.10f\n",proba);
            #endif
            listePaireHaplo = listePaireHaplo->next;
        }
        geno[i]->probaPrec = proba;
        #if 0
        printf("G%d - proba=%.10f\n",geno[i]->id,proba);
        #endif
    }
}

/* Calcul du log de la vraissemblance et mise à jour des proba pour chaque genotype */
static double estimation_esperance(int nbGeno, TypeGeno** geno, double** tabFreq)
{
    int i;
    double freqH1, freqH2, proba, ppart;
    double logLikelihood = 0;
    TypePaireHaplo* listePaireHaplo;
    for(i=0 ; i<nbGeno ; i++)
    {
        proba = 0;
        listePaireHaplo = geno[i]->first;
        while(listePaireHaplo != NULL)
        {
            freqH1 = recherche_frequence_precedente(listePaireHaplo->idHaplo1,tabFreq);
            freqH2 = recherche_frequence_precedente(listePaireHaplo->idHaplo2,tabFreq);
            if(listePaireHaplo->idHaplo1 == listePaireHaplo->idHaplo2)
            {
                ppart = freqH1 * freqH1;
            }
            else
            {
                ppart = 2 * freqH1 * freqH2;
            }
            proba = proba + ppart;
            listePaireHaplo = listePaireHaplo->next;
        }
        geno[i]->probaPrec = proba;
        logLikelihood = logLikelihood + geno[i]->nbIdentique * log10(proba);
        #if 0
        printf("proba = %f ; Log10 = %f ; NGeno = %d ; vraissemblance = %f\n",proba, log10(proba),geno[i]->nbIdentique,logLikelihood);
        #endif
    }
    return logLikelihood;
}


/* Recherche d'un genotype complet a partir d'un id */
static TypeGeno* recherche_genotype(int id, TypeGeno** geno)
{
    int i = 0;
    bool_t trouve = FALSE;
    TypeGeno* genoTrouve;
    while (trouve == FALSE)
    {
        if(id == geno[i]->id)
        {
            genoTrouve = geno[i];
            trouve = TRUE;
        }
        i++;
    }
    return genoTrouve;
}

/* Mise a jour du tableau de frequences d'haplotypes */
static void modification_frequence_precedente(int id, double freq, double** tabFreq)
{
    int i=0;
    bool_t trouve = FALSE;
    while (trouve == FALSE)
    {
        if(id == tabFreq[i][0])
        {
            tabFreq[i][2] = freq; /*Rempli la colonne des frequences precedentes*/
            trouve = TRUE;
        }
        i++;
    }
}

/* Calcul des frequences d'haplotypes */
static void maximisation(int nbHaplo, TypeHaplo** haplo, TypeGeno** geno, double** tabFreq)
{
    int i;
    double freqPrec1, freqPrec2, freq, contribution;
    TypeGenoExplique* listeGenoExp;
    TypeGeno* genoCourant;
    for(i=0 ; i<nbHaplo ; i++)
    {
        freqPrec1 = recherche_frequence_precedente(haplo[i]->id,tabFreq);
        #if 0
        printf("freqPrec1 : %.10f\n",freqPrec1);
        #endif
        freq = 0;
        /*Parcours de chaque liste chainee de genotype*/
        listeGenoExp = haplo[i]->first;
        while(listeGenoExp != NULL)
        {
            /*Recuperation des informations du genotype observe*/
            genoCourant = recherche_genotype(listeGenoExp->id, geno);
            #if 0
            printf("id : %d - id2 : %d ",haplo[i]->id,listeGenoExp->idHaploCompl);
            #endif
            /*Homozygotie*/
            if(haplo[i]->id == listeGenoExp->idHaploCompl)
            {
                contribution = 2.0*((freqPrec1 * freqPrec1)/genoCourant->probaPrec)*(genoCourant->nbIdentique/NB_INDIV);
            }
            else /*Heterozygotie*/
            {
                /*printf("id pour freqH2 : %d\n",listeGenoExp->idHaploCompl);*/
                freqPrec2 = recherche_frequence_precedente(listeGenoExp->idHaploCompl,tabFreq);
                contribution = 2.0*((freqPrec1 * freqPrec2)/genoCourant->probaPrec)*(genoCourant->nbIdentique/NB_INDIV);
                #if 0
                printf("Ngeno = %d - Ngeno/Nindiv = %f - ",genoCourant->nbIdentique,genoCourant->nbIdentique/NB_INDIV);
                printf("freqH2 : %.5f - ",freqPrec2);
                printf("Contribution : %.5f\n",contribution);
                #endif
            }
            freq = freq + contribution;
            listeGenoExp = listeGenoExp->next;
        }
        freq = freq/2.0;
        #if 0
        printf("freq = %.10f\n",freq);
        #endif
        modification_frequence_precedente(haplo[i]->id,freq,tabFreq);
    }
}

/* Mise à jour des probabilites de genotypes */
static void mise_a_jour_proba(int nbGeno, TypeGeno** tabGeno)
{
    int i;
    for(i=0 ; i < nbGeno ; i++)
    {
        tabGeno[i]->proba = tabGeno[i]->probaPrec;
    }
}

/* Mise à jour des frequences d'haplotypes */
static void mise_a_jour_freq(int nbHaplo, double** tabFreq)
{
    int i;
    for(i=0 ; i < nbHaplo ; i++)
    {
        tabFreq[i][1] = tabFreq[i][2];
    }
}

/* Verifie chiffre par chiffre si les 2 haplotypes sont egaux */
int verif_doublon(int* seq1, int* seq2)
{
    int verifPresenceDoublon = 1;
    int i = 0;
    while ((verifPresenceDoublon == 1)&&(i < TAILLE_GENO))
    {
        if(seq1[i] != seq2[i])
        {
            verifPresenceDoublon = 0;
            return verifPresenceDoublon;
        }
        i++;
    }
    /*** TEST 3 ***/
    /*** TEST 4 ***/
    return verifPresenceDoublon;
}

/* fonctions publiques ======================================================================= */

int* alloue_memoire()
{
    int* pointeur = NULL;
    pointeur = malloc(TAILLE_GENO * sizeof(int));
    if (pointeur == NULL)
    {
        fprintf(stderr,"Erreur d'allocation mémoire.\n");
        exit(1);
    }
    return pointeur;
}

/* Suppression du retour chariot donne par fgets */
int lire(char* chaine, int longueur, FILE* fichier)
{
    char* positionEntree = NULL;
  
    if (fgets(chaine, longueur, fichier) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        return 0;
    }
    else
    {
        return 1;
    }
}

/* Fonction de comparaison utilisee par la fonction qsort() */
int compare (const void *a, const void *b)
{
    double **pa = (double**)a;
    double **pb = (double**)b;
    double diff = (*pb)[1] - (*pa)[1];
    double ret = 0;
    if (diff > 0)
    {
            ret = 1;
    }
    else if (diff < 0)
    {
            ret = -1;
    }
    else
    {
            ret = 0;
    }
    return ret;
}

/* Initialisation des differents genotypes */
int initialisation_geno(TypeGeno* geno, int id)
{   
    int i, countLoci;           /* Compteur */
    
    /* Initialisation des parametres du genotype */
    geno->nbLociAmbigu = compte_nombre_loci_ambigu(*geno);
    geno->nbHaplo = pow(2,geno->nbLociAmbigu);
    geno->nbIdentique = 1;
    geno->doublon = 0;
    geno->proba = 0;
    countLoci = 0;

    /* Initialisation de la matriceHaplo */
    geno->matriceHaplo = malloc(sizeof(TypeHaplo) * (geno->nbHaplo));
    for(i=0 ; i < geno->nbHaplo ; i++){
        geno->matriceHaplo[i].haplotype = alloue_memoire();
        geno->matriceHaplo[i].id = id;
        geno->matriceHaplo[i].doublon = 0;
        id ++;
    }   

    /* Generation de tous les haplotypes differents possibles */
    for(i = 0 ; i < TAILLE_GENO ; i++ )
    {
        /* Permet de savoir a quelle position ambigu on se trouve */
        if(geno->genotype[i] == 1){
            countLoci ++;
        }
        generation_haplo_possibles(geno->matriceHaplo,geno->nbHaplo,countLoci,i,geno->genotype[i]);
    }
    #if 1
    printf("*********************\n");
    affichage_genotype(*geno);
    printf("---------------------\n");
    affichage_haplotypes(*geno);
    #endif
    /*** TEST 5 ***/

    return id;
}

/* Recherche de doublon(s) de genotypes */
void recherche_genotype_doublon(TypeGeno* geno1, TypeGeno* geno2)
{
    int verif = 0;
    /* Regarde parmi tous les haplotypes generes dans un second geno2 */
    verif=0;
    verif=verif_doublon(geno1->genotype,geno2->genotype);
    if (verif==1)
    {
        geno2->id = geno1->id;
        geno2->doublon = 1;
        geno1->nbIdentique = geno1->nbIdentique +1;
        /*printf("Genotype %d est redondant !\n",geno1->id);*/
        /*geno1->nbIdentique=geno1->nbIdentique+1;*/
    }
}

/* Modification du nombre de genotype identique au gentoype etudie */
void modification_nb_geno_identique(int id,TypeGeno* geno)
{
    int i;
    bool_t trouve = FALSE;
    while (trouve == FALSE)
    {
        if(id == geno[i].id)
        {
            geno[i].nbIdentique = +1;
            trouve = TRUE;
        }
        i++;
    }
}

/* Recherche de doublon(s) d'haplotypes */
void recherche_haplotype_doublon(TypeGeno* geno1, TypeGeno* geno2)
{
    /* i correspond à un haplotype de g1 */
    /* j correspond à un haplotype de g2 */
    int i, j; 
    int verif = 0;
    for(i=0 ; i<geno1->nbHaplo ; i++)
    {
        /* Regarde parmi tous les haplotypes generes dans un premier geno1 */
        for(j=0 ; j<geno2->nbHaplo ; j++)
        {
            /* Regarde parmi tous les haplotypes generes dans un second geno2 */
            verif=0;
            verif=verif_doublon(geno1->matriceHaplo[i].haplotype,geno2->matriceHaplo[j].haplotype);
            if (verif==1)
            {
                geno2->matriceHaplo[j].id = geno1->matriceHaplo[i].id;
                geno2->matriceHaplo[j].doublon=1;
            }
        }
    }
}

/* Calcul le nombre d'haplotypes non redondants */
int calcul_nb_haplo_non_redondant(TypeGeno* geno)
{
    int count = 0;
    int i,j; /*Compteur*/
    for (i=0 ; i<NB_INDIV ; i++)
    {
        for(j=0 ; j<geno[i].nbHaplo ; j++)
        {
            if (geno[i].matriceHaplo[j].doublon == 0){
                count ++;
            }
        }
    }
    return count;
}

/* Calcul le nombre d'haplotypes non redondants */
int calcul_nb_geno_non_redondant(TypeGeno* geno)
{
    int count = 0;
    int i; /*Compteur*/
    for (i=0 ; i<NB_INDIV ; i++)
    {
        if (geno[i].doublon == 0){
            count ++;
        }
    }
    return count;
}

/* Fonction de recherche d'haplotype complementaire par indice */
int recherche_haplo_complementaire(TypeGeno geno, int indice)
{
    int indiceComplementaire;
    if(geno.nbHaplo > 1)
    {
        indiceComplementaire = ((geno.nbHaplo-1) - indice); /*miroir*/ 
    }
    else
    {
        indiceComplementaire = indice;
    }
    
    return indiceComplementaire;
}

/* Allocation mémoire pour le tableau de frequence d'haplotype */
double** allouer_memoire_tableau_2d(int nb)
{
    int i;
    double** pointeur = NULL;
    pointeur = malloc(sizeof(double*) * nb);
    for(i=0 ; i<nb ; i++)
    {
        pointeur[i] = malloc(sizeof(double) * 3);
    }
    return pointeur;
}

/************ Fonctions d'inference d'haplotypes ************/

void inference_haplotype_em(double seuil,
    int nbGeno, int nbHaplo, int nbEtapeMax,
    double** tabFreq,
    TypeGeno** tabGeno,
    TypeHaplo** tabHaplo)
{
    /*Varaibles locales*/
    bool_t convergence = FALSE;
    int nbEtape = 0;
    double vraissemblance;
    double vraissemblancePrec = -1E+20;

    /*Debut*/
    calculer_proba_geno(nbGeno, tabGeno, tabFreq);
    while((convergence == FALSE) && (nbEtape < nbEtapeMax))
    {
        nbEtape++;
        maximisation(nbHaplo, tabHaplo, tabGeno, tabFreq);
        vraissemblance = estimation_esperance(nbGeno, tabGeno, tabFreq);
        printf("V = %.20f\n",vraissemblance);
        convergence = (fabs(vraissemblance-vraissemblancePrec)/vraissemblancePrec) <= seuil;
        #if 1
        printf("etape : %d => V : %f - VPrec: %f - ",nbEtape,vraissemblance,vraissemblancePrec);
        printf("calcul convergence : %.30f\n",fabs(vraissemblance-vraissemblancePrec)/vraissemblancePrec);
        #endif

        if(convergence == FALSE)
        {
            vraissemblancePrec = vraissemblance;
            mise_a_jour_proba(nbGeno, tabGeno);
            mise_a_jour_freq(nbHaplo, tabFreq);
        }
    }
    /*FIN*/
}

bool_t compare_tableaux_entiers(int *tab1, int *tab2, int taille)
{
    int i = 0;
    
    for (i=0; i < taille; i++) 
    {
        if (tab1[i] != tab2[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}