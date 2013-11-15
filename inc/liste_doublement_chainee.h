#ifndef H_LISTE_DOUBLEMENT_CHAINEE
#define H_LISTE_DOUBLEMENT_CHAINEE

/* liste_doublement_chaine.h */

/* structures ================================================================================ */

typedef struct TCellCol
{
    int col;
    float val;
    struct TCellCol* next;
}TCellCol;

typedef TCellCol* TPCol;

typedef struct TCellLig
{
    int lig;
    struct TCellLig* next;
    TPCol teteCol;
}TCellLig;

typedef TCellLig* TPLig;

typedef struct TMat
{
    TPLig teteLig;
    int nbLigMax;
    int nbColMax;
    float valDef;
}TMat;

/* fonctions publiques ======================================================================= */

void init_matrice(TMat* adrMat, int nbLignesMax, int nbColonnesMax, float valDefaut);
void recherche_col(TPCol teteCol, int j, TPCol* adrPtrCol, TPCol* adrPtrColPrec);
void recherche(TMat mat, int i, int j, TPLig* adrPtrLig, TPLig* adrPtrLigPrec,
               TPCol* adrPtrCol, TPCol* adrPtrColPrec);
void creation_affectation_case_1(TMat* adrMat, TPLig* adrPtrLigPrec, int i, int j, float val);
void creation_affectation_case_2(TPLig* adrPtrLig, TPCol* adrPtrColPrec, int j, float val);
void detruire_ligne_i_ou_tete(TMat* adrMat, TPLig* adrPtrLig);
void detruire_case(TMat* adrMat, TPLig ptrLigPrec, TPLig* adrPtrLig,
                   TPCol ptrColPrec, TPCol* adrPtrCol);
void modifier_valeur(TPCol adrPtrCol, float val);
void set(TMat* adrMat, int i, int j, float val);


#endif /* H_LISTE_DOUBLEMENT_CHAINEE */
