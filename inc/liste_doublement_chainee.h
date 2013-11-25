#ifndef H_LISTE_DOUBLEMENT_CHAINEE
#define H_LISTE_DOUBLEMENT_CHAINEE

/* liste_doublement_chainee.h */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

/* types ===================================================================================== */

typedef enum {
        FALSE,
        TRUE
} bool_t;

/* structures ================================================================================ */

typedef struct Case Case;
struct Case
{
	int id;
    Case* next;
    Case* prev;
};

typedef struct Liste
{
    int taille;     /* Nombre d'elements dans la liste */
    Case* premiere;
    Case* derniere;
}Liste;

/* fonctions ================================================================================= */

Liste* initialiser_liste();
void ajout_tete(Liste* liste, int id);
void ajout_queue(Liste* liste, int id);
void ajout_pos(Liste* liste, int id, int position);
void sup_pos(Liste* liste, int position);
void sup_case_id(Liste* liste, int id);
void sup_ids(Liste* liste, int id);
void suppression_liste(Liste** ptrListe);
Case* recherche_id(Liste* liste, int id);
void modif_liste(Liste* liste, int id, int new_id);
void affichage_liste(Liste* liste);
int taille_liste(Liste* liste);

#endif /* H_LISTE_DOUBLEMENT_CHAINEE */
