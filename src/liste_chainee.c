/* liste_chainee.c */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/liste_chainee.h"

/* fonctions publiques ======================================================================== */

/* Fonction de creation d'un element de la liste */
TPointer creer_cell(int val)
{
    TPointer ptr = NULL;
    ptr = (TCell*)malloc(sizeof(TCell));
    if (ptr == NULL)
    {
        printf("Plus d'espace memoire \n");
        exit(1);
    }
    ptr->info = val;
    return ptr;
}

/* Fonction permettant de parcourir une liste */
void parcours_liste(TPointer tete)
{
    TPointer ptr = tete;
    while(ptr != NULL)
    {
        printf("%d\n",ptr->info);
        ptr = ptr->next;
    }
}

/* Fonction permettant d'inserer un element en tete de liste */
void ajout_tete(TPointer* adrTete, int val)
{
    TPointer ptr;
    ptr = creer_cell(val);
    ptr->next = *adrTete;
    *adrTete = ptr;

}

/* Fonction d'ajout d'un element suivant un ordre croissant
 * /!\ La liste doit être vide ou triée
 */
void ajout_tri(TPointer* adrTete, int val)
{
    TPointer pCourant, pPreced, ptr;
    pCourant = *adrTete;
    pPreced = NULL;
    while ((pCourant != NULL) && (val>pCourant->info))
    {
        pPreced = pCourant;
        pCourant = pCourant->next;
    }
    if((pPreced == NULL))
    {
        ajout_tete(adrTete,val);
    }
    else
    {
        ptr = creer_cell(val);
        ptr->next = pCourant;
        pPreced->next = ptr;
    }
}

/* point d'entree ============================================================================= */

int main()
{
    
    /* ====== Declarations ====== */
    
    TPointer p1 = NULL;
    
    /* ========== Code ========== */
    
    p1 = creer_cell(54);   
    ajout_tete(&p1,42);
    ajout_tri(&p1,45);
    parcours_liste(p1);
    return 0;
}
