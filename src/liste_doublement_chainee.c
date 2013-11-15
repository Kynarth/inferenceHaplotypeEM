/* liste_chainee.c */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/liste_doublement_chainee.h"

/* fonctions privees ========================================================================= */

static TPCol allouer_memoire_colonne()
{
        TPCol colonne = (TPCol)malloc(sizeof(TCellCol));
        if(colonne == NULL)
        {
            fprintf(stderr,"Echec de l'allocation mémoire \n");
            exit(1);
        }
        
        return colonne;
}

static TPLig allouer_memoire_ligne()
{
        TPLig ligne = (TPLig)malloc(sizeof(TCellLig));
        if(ligne == NULL)
        {
            fprintf(stderr,"Echec de l'allocation mémoire \n");
            exit(1);
        }
        
        return ligne;
}

/* fonctions publiques ======================================================================= */

/* Fonction d'initialisation de la matrice */
void init_matrice(TMat* adrMat, int nbLignesMax, int nbColonnesMax, float valDefaut)
{
    adrMat->teteLig = NULL;
    adrMat->nbLigMax = nbLignesMax;
    adrMat->nbColMax = nbColonnesMax;
    adrMat->valDef = valDefaut;
}

/* Fonction renvoyant la position de la colonne recherchee */
void recherche_col(TPCol teteCol, int j, TPCol* adrPtrCol, TPCol* adrPtrColPrec)
{
    TPCol pcc = teteCol; /* Pointeur Colonne Courant */
    TPCol pcp = NULL;    /* Pointeur Colonne Precedent */
    
    /* Parcours la liste de colonne de la ligne i */
    while((pcc != NULL) && (pcc->col < j))
    {
        pcp = pcc;
        pcc = pcc->next;
    }
    /* Depasse la valeur j */
    if((pcc != NULL) && (pcc->col > j))
    {
        pcc = NULL;
    }
    *adrPtrCol = pcc;
    *adrPtrColPrec = pcp;
}

/* Fonction renvoyant la position de la ligne et de la colonne recherchee */
void recherche(TMat mat, int i, int j, TPLig* adrPtrLig, TPLig* adrPtrLigPrec,
               TPCol* adrPtrCol, TPCol* adrPtrColPrec)
{
    TPLig plc = mat.teteLig; /* Pointeur Ligne Courant */
    TPLig plp = NULL;        /* Pointeur Ligne Precedent */

    while((plc != NULL) && (plc->lig < i))
    {
        plp = plc;
        plc = plc->next;
    }
    *adrPtrLig = plc;
    *adrPtrLigPrec = plp;
    
    if(plc != NULL) /* Liste de lignes non vide */
    { 
        if(plc->lig == i) /* La ligne i est presente dans la liste */
            recherche_col(plc->teteCol, j, adrPtrCol, adrPtrColPrec);
        else
            plc = NULL; /*Ligne vide*/
            
        *adrPtrLig = plc;
        *adrPtrLigPrec = plp;
        
    }
}

/* Fonction de création de ligne et sa premiere colonne */
void creation_affectation_case_1(TMat* adrMat, TPLig* adrPtrLigPrec, int i, int j, float val)
{
    TPLig ligne = allouer_memoire_ligne();
    TPCol colonne = allouer_memoire_colonne();
    
    ligne->lig = i;
    if(adrPtrLigPrec == NULL)
    {
        ligne->next = adrMat->teteLig;
        adrMat->teteLig = ligne;
    }
    else
    {
        ligne->next = (*adrPtrLigPrec)->next;
        (*adrPtrLigPrec)->next = ligne;
    }
    colonne->val = val;
    colonne->col = j;
    colonne->next = NULL;
    ligne->teteCol = colonne;
}

/* Fonction de creation de colonne */
void creation_affectation_case_2(TPLig* adrPtrLig, TPCol* adrPtrColPrec, int j, float val)
{
    TPCol colonne = allouer_memoire_colonne();
    
    colonne->val = val;
    colonne->col = j;
    
    if(adrPtrColPrec == NULL) /* Pas de colonne dans la ligne */
    {
        colonne->next = (*adrPtrLig)->teteCol;
        (*adrPtrLig)->teteCol = colonne;
    }
    else
    {
        colonne->next = (*adrPtrColPrec)->next;
        (*adrPtrColPrec)->next = colonne;
    }
}

void detruire_ligne_i_ou_tete(TMat* adrMat, TPLig* adrPtrLig)
{
    
}

/* Fonction supprimant une case colonne */
void detruire_case(TMat* adrMat, TPLig ptrLigPrec, TPLig* adrPtrLig,
                   TPCol ptrColPrec, TPCol* adrPtrCol)
{
    if(ptrColPrec == NULL)
    {
        (*adrPtrLig)->teteCol = (*adrPtrCol)->next;
        if((*adrPtrLig)->teteCol == NULL)
        {
            detruire_ligne_i_ou_tete(adrMat,adrPtrLig);
        }
    }
    else
    {
        ptrColPrec->next = (*adrPtrCol)->next;
    }
    free(*adrPtrCol);
}

/* Fonction modifiant la valeur d'une colonne */
void modifier_valeur(TPCol adrPtrCol, float val)
{
    adrPtrCol->val = val;
} 

/* Fonction ???? */
void set(TMat* adrMat, int i, int j, float val)
{
    TPLig plc = NULL; /*Pointer Ligne Courant*/
    TPLig plp = NULL; /*Pointer Ligne Precedent*/
    TPCol pcc = NULL; /*Pointer Colonne Courant*/
    TPCol pcp = NULL; /*Pointer Colonne Precedent*/
    
    recherche(*adrMat,i,j,&plc,&plp,&pcc,&pcp);
    if(plc == NULL)
    {
        if(val != adrMat->valDef)
            creation_affectation_case_2(&plc,&pcp,j,val);
    }
    else
    {
        if(val == adrMat->valDef)
            detruire_case(adrMat,plp,&plc,pcp,&pcc);
        else
            modifier_valeur(pcc,val);
    }
}

/* point d'entree ============================================================================ */

int main(){
    
    /* ====== Declarations ====== */
    
    TMat matrice;
    TPLig ptr_lig = NULL;
    TPLig ptr_lig_prec = NULL;
    TPCol ptr_col = NULL;
    TPCol ptr_col_prec = NULL;
    
    /* ========== Code ========== */
    
    /* Initialisation matrice */
    init_matrice(&matrice,10,5,0);
    /* Creation premiere ligne */
    creation_affectation_case_1(&matrice, NULL, 1, 1, 17);
    /* Cherche pointeur sur nouvelle ligne */
    recherche(matrice, 1, 1, &ptr_lig, &ptr_lig_prec, &ptr_col, &ptr_col_prec);
    printf("numero de a ligne courante: %d\n", ptr_lig->lig);
    printf("valeur de colonne de la ligne courante: %f\n", ptr_col->val);
    
    /* Creation 2eme ligne a la suite de la premiere */
    creation_affectation_case_1(&matrice, &ptr_lig, 2, 1, 23);
    /* Verifivcation ligne 1 liee a ligne 2 */
    printf("Numero de ligne de la ligne suivante à la ligne courante: %d\n", ptr_lig->next->lig);
    /* Cherche pointeur sur nouvelle ligne */
    recherche(matrice, 2, 1, &ptr_lig, &ptr_lig_prec, &ptr_col, &ptr_col_prec);
    printf("numero de ligne précédente: %d\n", ptr_lig_prec->lig);
    printf("valeur de la colonne 1 de la ligne 2: %f\n", ptr_col->val);
    
    /* creation de la colonne 2 dans la ligne 2 */
    creation_affectation_case_2(&ptr_lig, &ptr_col, 2, 33);
    /* recuperation des pointeurs sur la nouvelle colonne */
    recherche(matrice, 2, 2, &ptr_lig, &ptr_lig_prec, &ptr_col, &ptr_col_prec);
    /* verification pointeurs */
    printf("Valeur de la colonne 1 ligne 2: %f\n", ptr_col_prec->val);
    printf("Valeur de la colonne 2 ligne 2 via colonne 1: %f\n", ptr_col_prec->next->val);
    printf("Valeur de la colonne 2 ligne 2: %f\n", ptr_col->val);
    
    detruire_case(&matrice, ptr_lig_prec, &ptr_lig, ptr_col_prec, &ptr_col);
    
    return 0;
}
