/* main.c */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../inc/fonctions.h"

/* point d'entree ============================================================================ */

int main(int argc,char* argv[])
{
    
	/* ====== Declarations ====== */
    
	int i, j; /* compteurs */
	TypeBool doublon;
	TypeHaplo* haplo = NULL;
	TypeGeno* geno = NULL;
    FILE* fichier = NULL;
    
    /* ========== Code ========== */
    
	if (argc != 4)
    {
	    printf("Le nombre d'argument est incorrect !\n");
	    printf("la commande doit etre du type :\n");
	    printf("./main nb_individu(entier) taille_genome(entier) nb_de_loci(entier)\n");
	    exit(1);	
	}
	for (i=1 ; i < argc ; i++)
    {
	    if (atoi(argv[i]) == 0)
        {
	        printf("Impossible d'avoir un paramêtre nul ou contenant un caractère\n");
	        exit(1);
	    }
	}
    
    srand (time(NULL));
	
    /* Suppression des fichiers de genotypes si presents */
	test_existence(GENO_HAPLO);
	test_existence(GENOTYPES);
    
	nbIndiv = atoi(argv[1]);
	tailleGeno = atoi(argv[2]);
	nbLoci = atoi(argv[3]);
    if (tailleGeno <= nbLoci)
    {
        printf("Le nombre de loci ambigu maximum doit etre inferieur à la taille du genotype.\n");
        exit(1);
    }
	nbHaplo = 0.7*2*nbIndiv;
    
    haplo = malloc(NB_HAPLO * sizeof(TypeHaplo));
    geno = malloc(NB_INDIV * sizeof(TypeGeno));

	/* Initialisation du tableau d'haplotypes */
	for (i=0 ; i < NB_HAPLO ; i++)
    {
		haplo[i].id=i;
        initialiser_haplotypes(&haplo[i]);
	}

	/*
     * parcours la liste d'haplotypes pour verifier l'absence de doublon.
     * si un doublon est present, le premier croise obtient un VRAI
     * dans l'element doublon.
	 */
	for (i=0 ; i < NB_HAPLO ; i++)
    {
		j = i+1;
		doublon = 0;
		while ((doublon == 0) && (j < NB_HAPLO))
        {
			doublon = verification_presence_doublon(haplo[i],haplo[j]);
			j++;
		}
		haplo[i].doublon=doublon;
		/*(test)afficher_haplotypes(haplo[i],TAILLE_GENO);*/
	}

	for (i = 0 ; i < NB_INDIV ; i++)
    {
		geno[i].id=i;
		initialiser_genotypes(&geno[i],haplo);
	}
    
    /* (test)Affichage des résultats */
	printf("nb de genotypes générés : %d \n",NB_INDIV);
	printf("nb d'haplotypes générés : %d \n",NB_HAPLO);
	printf("taille du genome : %d \n",TAILLE_GENO);
	printf("nb de loci differents tolere : %d \n",NB_LOCI);
    
    /* Stockage des parametres dans un fichier */
    fichier = fopen(PARAM, "w");
    if ( fichier != NULL)
    {
        fprintf(fichier, "%d\t%d\t%d\n", NB_INDIV, TAILLE_GENO, NB_LOCI);
    }
    else
    {
        fprintf(stderr, "Une erreur s'est produite dans la création du fichier %s", PARAM);
        exit(1);
    }
    fclose(fichier);
    
    free(haplo);
    free(geno);
	
    return 0;
}
