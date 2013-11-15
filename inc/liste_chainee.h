#ifndef H_LISTE_CHAINEE
#define H_LISTE_CHAINEE

/* liste_chaine.h */

/* structures ================================================================================= */

typedef struct TCell
{
    int info;
    struct TCell* next;
}TCell;

typedef TCell* TPointer;

/* fonctions publiques ======================================================================== */

TPointer creer_cell(int val);
void parcours_liste(TPointer tete);
void ajout_tete(TPointer* adrTete, int val);
void ajout_tri(TPointer* adrTete, int val);

#endif /* H_LISTE_CHAINEE */
