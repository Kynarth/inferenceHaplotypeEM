/* inference_main.c */

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

/* point d'entree ============================================================================ */

int main(int argc, char* argv[])
{  
    /* ====== Declarations ====== */

    int c, i = 0; /* compteurs */
    int j;
    int id=0;
    int nbLoci = 0;
    int compl=0;
    int nbHaploNonRedondant = 0;
    int lireTaille = 0;         /* taille memoire pour la lecture de ligne */
    char* nomFichier;           /* fichier contenant les genotypes */
    char* chaine = NULL;        /* chaine qui contiendra les lignes du fichier geno */
    char* sousChaine = NULL;    /* pointeur sur la partie code du genome */
    FILE* fichier = NULL;       
    FILE* fichierParam = NULL;
    TypeGenoBase* geno = NULL;
    TypeHaploBase* haploNonRedondant = NULL;
    /*TypeHaplo* teteHaplo = NULL; */

     /* ========== Code ========== */
    
    if (argc != 2)
    {
        printf("Le nombre d'argument est incorrect !\n");
        printf("la commande doit etre du type :\n");
        printf("./__FILE__ fichier_genotype(chaine) \n");
        exit(1);    
    }
    
    nomFichier = argv[1];
    
    fichier = fopen(nomFichier, "r");
    if (fichier != NULL)
    {
        fichierParam = fopen(PARAM, "r");
        if (fichierParam != NULL)
        {
            fscanf(fichierParam, "%d", &nbIndiv);
            fscanf(fichierParam, "%d", &tailleGeno);
            fscanf(fichierParam, "%d", &nbLoci);
        }
        else
        {
            fprintf(stderr, "Une erreur s'est produite dans la création du fichier %s\n", PARAM);
            exit(1);
        }
        fclose(fichierParam);
        
        /* Determination de la taille d'une ligne */
        while((c != '\n') && (c != EOF))
        {
            c = fgetc(fichier);
            lireTaille++;
        }
        /* taille de la ligne + '\0' + augmentation de caracteres par nbIndiv: 10->100->1000.. */
        lireTaille = lireTaille + 1 + (int)((log10(NB_INDIV) + 1)); 
        
        fseek(fichier, 0, SEEK_SET);
        chaine = (char*)malloc(sizeof(char) * lireTaille);
        
        /* Stockage des genotypes du fichier dans un tableau de structures */
        c = 0;
        geno = malloc(sizeof(TypeGenoBase) * NB_INDIV);
        for(i=0; i < NB_INDIV; i++)
        {
            geno[i].genotype = (int*)malloc(sizeof(int) * TAILLE_GENO);
        }
        while((lire(chaine, lireTaille, fichier) == 0))
        {
            geno[c].id = c;
            sousChaine = strchr(chaine, '\t');
            sousChaine = sousChaine + 1;
            if(sousChaine != NULL)
            {
                for(i=0; i < TAILLE_GENO; i++)
                {
                    geno[c].genotype[i] = sousChaine[i] - '0';
                    /*printf("%d",geno[c].genotype[i]);*/
                }
                c++;
                /*printf("\n");*/
            }
        }
        free(chaine);
    }
    else
    {
        fprintf(stderr, 
                "Une erreur s'est produite durant l'ouverture du fichier des génotypes.\n");
        exit(1);
    }


    /* Generation des haplotypes possibles */
    for(i=0 ; i<NB_INDIV ; i++)
    {
        /* Recuperation de l'id afin d'identifier tous les haplotypes avec un id different */
        id = initialisation_geno(&geno[i],id); 
    }

    /* Indique pour chaque genotype et haplotype si c'est un doublon ou non */
    for (i=0 ; i < NB_INDIV ; i++)
    {
        j = i+1;
        while (j < NB_INDIV)
        {
            /* Verification des genotypes identiques et remplacement de l'id 
             * en cas de similarite */ 
            recherche_genotype_doublon(&geno[i],&geno[j]);
            if(geno[i].id!=geno[j].id)
            {
                recherche_haplotyple_doublon(&geno[i],&geno[j]);
            }
            j++;
        }
        /*(test)afficher_haplotypes(haplo[i],TAILLE_GENO);*/
    }
    printf("nb de geno 6 : %d\n",geno[6].nbIdentique);
    nbHaploNonRedondant = calcul_nb_haplo_non_redondant(geno);
    printf("nbHaploNonRedondant = %d\n", nbHaploNonRedondant);
    haploNonRedondant = malloc(sizeof(TypeHaploBase) * nbHaploNonRedondant);
    c = 0;
    for (i=0 ; i < NB_INDIV ; i++)
    {
        for (j=0 ; j<geno[i].nbHaplo ; j++)
        {
            if (geno[i].matriceHaplo[j].doublon == 0)
            {
                haploNonRedondant[c] = geno[i].matriceHaplo[j];
                c++;
            }
        }
    }
    /*for (i=0 ; i < nbHaploNonRedondant ; i++)
    {
        printf("%d : ",haploNonRedondant[i].id);
        for (j=0 ; j < TAILLE_GENO ; j++)
        {
            printf("%d",haploNonRedondant[i].haplotype[j]);
        }
        printf("\n");
    }*/
    /*creation_liste(haploNonRedondant, geno,nbHaploNonRedondant);*/
    /*compl=recherche_haplo_complementaire(haploNonRedondant[0], geno[0]);*/
    printf("Complementaire : %d\n",compl);
    fclose(fichier);
    free(geno);
    
    return 0;
}
