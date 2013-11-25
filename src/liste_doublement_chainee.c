/* liste_doublement_chainee.c */

/*
 * Auteurs: Julie Pelletier
 *          Nicolas Belouin
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/liste_doublement_chainee.h"

/* fonctions publiques ======================================================================= */

/* Focntion d'initilisation d'une liste chainee */
Liste* initialiser_liste()
{
    Liste* liste = malloc(sizeof(Liste*));
    if (liste == NULL)
    {
        fprintf(stderr, "Un problème d'allocation mémoire est survenu.\n");
        exit(1);
    }
    
    liste->taille = 0;
    liste->premiere = NULL;
    liste->derniere = NULL;
    
    return liste;
}

/* Fonction d'ajout d'un element en debut de liste */
void ajout_tete(Liste* liste, int id)
{
    if (liste != NULL)
    {
        /* Creation du nouvel element de la liste */
        Case* nouvelleCase = malloc(sizeof(Case*));
        if (nouvelleCase == NULL)
        {
            fprintf(stderr, "Un problème d'allocation mémoire est survenu.\n");
            exit(1);
        }
        nouvelleCase->id =id;
        nouvelleCase->prev = NULL;
        
        /* Cas ou la liste est vide */
        if (liste->premiere == NULL)
        {
            liste->premiere = nouvelleCase;
            liste->derniere = nouvelleCase;
            nouvelleCase->next = NULL;
        }
        else
        {
            nouvelleCase->next = liste->premiere;
            liste->premiere->prev = nouvelleCase;
            liste->premiere = nouvelleCase;
        }
        liste->taille++; /* Incrementation de la taille de la liste */
    }  
}

/* Fonction d'ajout d'un element en fin de liste */
void ajout_queue(Liste* liste, int id)
{
    if (liste != NULL)
    {
        /* Creation du nouvel element de la liste */
        Case* nouvelleCase = malloc(sizeof(Case*));
        if (nouvelleCase == NULL)
        {
            fprintf(stderr, "Un problème d'allocation mémoire est survenu.\n");
            exit(1);
        }
        nouvelleCase->id =id;
        nouvelleCase->next = NULL;
        
        /* Cas ou la liste est vide */
        if (liste->derniere == NULL)
        {
            nouvelleCase->prev = NULL;
            liste->premiere = nouvelleCase;
            liste->derniere = nouvelleCase;
        }
        else
        {
            nouvelleCase->prev = liste->derniere;
            liste->derniere->next = nouvelleCase;
            liste->derniere = nouvelleCase;
        }
        liste->taille++; /* Incrementation de la taille de la liste */
    }
}

/* Fonction permettant l'ajout d'un element a la position souhaitee */
void ajout_pos(Liste* liste, int id, int position)
{
    int i = 1;          /* Compteur */
    Case* ptr = NULL;   /* Pointeur de parcours de liste */
    
    
    if (liste != NULL)
    {
        ptr = liste->premiere;
        
        while ((i <= position) && (ptr != NULL))
        {
            if (position == i)
            {
                /* Cas ou position est en fin de liste */
                if (ptr->next == NULL)
                {
                    ajout_queue(liste, id);
                }
                /* Cas ou position est en tete de liste */
                else if (ptr->prev == NULL)
                {
                    ajout_tete(liste, id);
                }
                else
                {
                    /* Creation du nouvel element de la liste */
                    Case* nouvelleCase = malloc(sizeof(Case*));
                    if (nouvelleCase == NULL)
                    {
                        fprintf(stderr, "Un problème d'allocation mémoire est survenu.\n");
                        exit(1);
                    }
                    nouvelleCase->id =id;
                    ptr->next->prev = nouvelleCase;
                    ptr->prev->next = nouvelleCase;
                    nouvelleCase->prev = ptr->prev;
                    nouvelleCase->next = ptr;
                    liste->taille++;
                }
            }
            else
            {
                ptr = ptr->next;
            }
            i++;
        }
    }
}

/* Fonction supprimant un element en fonction de sa position */
void sup_pos(Liste* liste, int position)
{
    int i = 1;                   /* Compteur */
    Case* ptr = liste->premiere; /* Pointeur de parcours de liste */
    
    if (liste != NULL)
    {
        while ((ptr != NULL) && (i <= position))
        {
            if (position == i)
            {
                /* Cas ou l'on se trouve en fin de liste */
                if (ptr->next == NULL)
                {
                    liste->derniere = ptr->prev;
                    liste->derniere->next = NULL;
                }
                /* Cas ou l'on se trouve en début de liste */
                else if (ptr->prev == NULL)
                {
                    liste->premiere = ptr->next;
                    liste->premiere->prev = NULL;
                }
                else
                {
                    ptr->next->prev = ptr->prev;
                    ptr->prev->next = ptr->next;
                }
                free(ptr);
                liste->taille--;
            }
            else
            {
                ptr = ptr->next;
            }
            i++;
        }
    }
}

/* Fonction supprimant la case contenant l'id passe en parametre */
void sup_case_id(Liste* liste, int id)
{
    bool_t trouve = 0;
    Case* ptr = liste->premiere; /* Pointeur de parcours de liste */
    
    if (liste != NULL)
    {
        while ((ptr != NULL) && (!trouve))
        {
            if (ptr->id == id)
            {
                /* Cas ou l'on se trouve en fin de liste */
                if (ptr->next == NULL)
                {
                    liste->derniere = ptr->prev;
                    liste->derniere->next = NULL;
                }
                /* Cas ou l'on se trouve ne debut de liste */
                else if (ptr->prev == NULL)
                {
                    liste->premiere = ptr->next;
                    liste->premiere->prev = NULL;
                }
                else
                {
                    ptr->next->prev = ptr->prev;
                    ptr->prev->next = ptr->next;
                }
                free(ptr);
                liste->taille--;
                trouve = 1;
            }
            else
            {
                ptr=ptr->next;
            }
        }
        
    }
}

/* Fonction supprimant tous les elements ayant le meme id */
void sup_ids(Liste* liste, int id)
{
    Case* ptr = liste->premiere; /* Pointeur de parcours de liste */
    
    if (liste != NULL)
    {
        while (ptr != NULL)
        {
            if (ptr->id == id)
            {
                /* Cas ou l'on se trouve en fin de liste */
                if (ptr->next == NULL)
                {
                    liste->derniere = ptr->prev;
                    liste->derniere->next = NULL;
                }
                /* Cas ou l'on se trouve ne debut de liste */
                else if (ptr->prev == NULL)
                {
                    liste->premiere = ptr->next;
                    liste->premiere->prev = NULL;
                }
                else
                {
                    ptr->next->prev = ptr->prev;
                    ptr->prev->next = ptr->next;
                }
                free(ptr);
                liste->taille--;
            }
            else
            {
                ptr=ptr->next;
            }
        }
        
    }
}

/* Fonction supprimant entierement la liste chainee */
void suppression_liste(Liste** ptrListe)
{
    Case* ptr = (*ptrListe)->premiere; /* pointeur de parcours de liste */
    Case* ptrDel = NULL;               /* pointeur de suppression d'element */
    
    if (*ptrListe != NULL)
    {
        while (ptr != NULL)
        {
            ptrDel = ptr;
            ptr = ptr->next;
            free(ptrDel);
        }
        free(*ptrListe);
        *ptrListe = NULL;
    }
}

/* Fonction de recherche en fonction de l'id */
Case* recherche_id(Liste* liste, int id)
{
    Case* ptr = liste->premiere; /* Pointeur de parcours de liste */
    
    if (liste != NULL)
    {
        while (ptr != NULL)
        {
            if (ptr->id == id)
            {
                return ptr;
            }
            else
            {
                ptr=ptr->next;
            }
        }
        
    }
    
    return ptr;
}

/* Fonction modifiant les informations d'un element de la liste */
void modif_liste(Liste* liste, int id, int new_id)
{
    Case* ptr = recherche_id(liste, id);
    if (ptr == NULL)
    {
        fprintf(stderr, "La modification de liste n'a pu se faire.\n");
        return;
    }
    else
    {
        ptr->id = new_id;
    }
}

/* Fonction affichant chaque element de la liste */
void affichage_liste(Liste* liste)
{
    Case* ptr = liste->premiere; /* Poitneur de parcours de liste */
    
    if (liste != NULL)
    {
        while (ptr != NULL)
        {
            printf("%d > ", ptr->id);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
    else
    {
        printf("La liste est vide.\n");
    }
}

/* Fonction retournant la taille d'une liste */
int taille_liste(Liste* liste)
{
    int taille = 0;
    
    if (liste != NULL)
    {
        taille = liste->taille;
    }
    
    return taille;
}


/* point d'entree ============================================================================ */
#if 0
int main()
{
    /* ====== Declarations ====== */
    
    int taille = 0;
    Liste* liste = initialiser_liste();
    Case* test = NULL;
    
    /* ========== Code ========== */
    
    ajout_queue(liste, 2);
    ajout_tete(liste, 1);
    ajout_queue(liste, 4);
    ajout_pos(liste, 3, 3);
    sup_case_id(liste, 3);   
    affichage_liste(liste);
    if (test != NULL)
    {
        printf("L'id de la case 3 est %d\n", test->id);
    }
    
    ajout_pos(liste, 3, 3);
    ajout_pos(liste, 3, 4);
    ajout_pos(liste, 4, 6);
    sup_ids(liste, 3);
    sup_pos(liste, 3);
    affichage_liste(liste);
    
    suppression_liste(&liste);
    liste = initialiser_liste();
    ajout_tete(liste, 1);
    affichage_liste(liste);
    taille = taille_liste(liste);
    printf("la taille de la liste est de %d\n", taille);
    
    test = recherche_id(liste, 1);
    if (test != NULL)
    {
        printf("L'id de la case ayant l'id 1 est %d\n", test->id);
    }
    modif_liste(liste, 1, 4);
    affichage_liste(liste);
    
    return 0;
}
#endif
