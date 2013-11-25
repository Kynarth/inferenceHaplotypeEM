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

/* fonctions privees ========================================================================= */

/* Compte le nombre de loci ambigu pour un genotype donnee */
static int compte_nombre_loci_ambigu(TypeGenoBase geno)
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
static void generation_haplo_possibles(TypeHaploBase* matrice, int lociMax, 
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

static void affichage_haplotypes(TypeGenoBase geno)
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

/* Verifie chiffre par chiffre si les 2 haplotypes sont egaux */
static int verif_doublon(int* seq1, int* seq2)
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
    /* (test)Affichage de doublon lorsqu'il y en a un de present */
    /* (test)printf("doublon-%d\n",verifPresenceDoublon);*/
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

/* Initialisation des differents genotypes */
int initialisation_geno(TypeGenoBase* geno, int id)
{   
    int i, countLoci;           /* Compteur */
    
    /* Initialisation des parametres du genotype */
    geno->nbLociAmbigu = compte_nombre_loci_ambigu(*geno);
    geno->nbHaplo = pow(2,geno->nbLociAmbigu);
    geno->nbIdentique = 1;
    countLoci = 0;

    /* Initialisation de la matriceHaplo */
    geno->matriceHaplo = malloc(sizeof(TypeHaploBase) * (geno->nbHaplo));
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

    /* Affichages */
    printf("*********************\n");
    affichage_genotype(*geno);
    printf("---------------------\n");
    affichage_haplotypes(*geno);
    return id;
}

/*void recherche_haplotyple_doublon(TypeGenoBase* geno1, TypeGenoBase* geno2)
{
    int i, j; 
    int verif = 0;
    for(i=0 ; i<geno1->nbHaplo ; i++)
    {
        if(geno1->matriceHaplo[i].doublon != 1)
        {
            j=0;
            while((j<geno2->nbHaplo)&&(verif == 0))
            {
                verif = verif_doublon(geno1->matriceHaplo[i].haplotype,geno2->matriceHaplo[j].haplotype);            
                geno2->matriceHaplo[j].doublon = 0;
                j++;
            }
            geno2->matriceHaplo[j].doublon = verif;
        }  
    }
}*/

void recherche_genotype_doublon(TypeGenoBase* geno1, TypeGenoBase* geno2)
{
    int verif = 0;
    /* Regarde parmi tous les haplotypes generes dans un second geno2 */
    verif=0;
    verif=verif_doublon(geno1->genotype,geno2->genotype);
    if (verif==1)
    {
        geno2->id = geno1->id;
        printf("Genotype %d est redonant !\n",geno1->id);
        /* Permet de savoir combien de genotypes seront identique pour le geno1 (de reference) */
        geno1->nbIdentique=geno1->nbIdentique+1;
    }
}

/* C'EST ICI QU'IL FAUDRAIT FAIRE LE REMPLISSAGE DES LISTES CHAINEES DE GENOTYPES */
void recherche_haplotyple_doublon(TypeGenoBase* geno1, TypeGenoBase* geno2)
{
    /* i correspond au genotype h1 */
    /* j correspond au genotype h2* /
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

int calcul_nb_haplo_non_redondant(TypeGenoBase* geno)
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

void affichage_genotype(TypeGenoBase geno)
{
    int i;
    printf("%d : ",geno.id);
    for(i = 0 ; i < TAILLE_GENO ; i++ )
    {
        printf("%d",geno.genotype[i]);
    }
    printf("\n");
}

void affichage_haplotype(TypeHaploBase haplo)
{
    int j;
        printf("%d : ",haplo.id);
        for(j = 0 ; j < TAILLE_GENO ; j++)
        {
           printf("%d",haplo.haplotype[j]); 
        }
        printf("\n");
}
