/* liste_chainee_haplotypes.c */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/generation_haplotypes.h"
#include "../inc/liste_chainee_haplotypes.h" 

/* fonctions publiques ======================================================================= */

/*
void creation_liste(TypeHaploBase* listeHaplo, TypeGenoBase* listeGeno, int nbHaploNonRedondant)
{
    int i;
    int j;
    for (i=0 ; i<nbHaploNonRedondant ; i++)
    {
        printf("");
    }
}*/

int recherche_haplo_complementaire(TypeHaploBase haploRef, TypeGenoBase geno)
{   
    int i;
    int j;
    int verifHaplo=0;
    int verif;
    int complementaire;
    int* haploTeste;

    i=0;
    while((verifHaplo==0)&&(i<geno.nbHaplo))
    {
        j=0;
        haploTeste = geno.matriceHaplo[i].haplotype;
        verif=1;
        while((verif==1)&&(j<TAILLE_GENO))
        {
            if((geno.genotype[j]==2)&&(haploTeste[j]==0))
                verif=0;
                
            else if((geno.genotype[j]==0)&&(haploTeste[j]==1))
                verif=0;
            else if(geno.genotype[j]==1)
            {
                if((haploRef.haplotype[j]==1)&&(haploTeste[j]==1))
                    verif=0;
                else if((haploRef.haplotype[j]==0)&&(haploTeste[j]==0))
                    verif=0;
            }
            
            if((verif==1)&&(j==TAILLE_GENO-1))
            {
                complementaire=geno.matriceHaplo[i].id;
                verifHaplo=1;
            }
            j++;
        }
        i++;
    } 
    return complementaire;
}
