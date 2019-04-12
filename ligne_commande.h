#ifndef LIGNE_COMMANDE_H_INCLUDED
#define LIGNE_COMMANDE_H_INCLUDED
#include "produit.h";
//structue de la  ligne de commande
typedef struct ligne_commande ligne_commande;
struct ligne_commande
{
    int ID_Cmd;
    int quantite;
    float subTotal;
    produit* produit;


};
// structure de la liste de commande;
typedef struct ElementCommande ElementCommande;
struct ElementCommande
{
    ligne_commande* ligne_commande;
    ElementCommande* nxt;


};
ligne_commande* Creat_ligne_commande(produit* produit ,int quantite,int ID_Cmd);
ElementCommande* CreatElementCommande(produit* produit,int quantite,int ID_Cmd );
ElementCommande* ajouterCommandeElement(ElementCommande* listCommande , produit* produit,int quantite,int ID_Cmd);
void display_ligne_commande(ligne_commande*  commande);
void display_liste_commande(ElementCommande* listCommande);
int test_list_commande(ElementCommande* listCommande);
ElementCommande* ajouterCommande(ElementCommande* listCommande);
ElementCommande* supprimer_ligne_de_commande(ElementCommande* listCommande,int code);
ligne_commande* Recherche_ligne_de_commande(ElementCommande* listCommande , int code);
ElementCommande* mainCommande(ElementCommande* listCmd);
ElementCommande*  modifier_commande(ElementCommande* listCommande,int code);


#endif // LIGNE_COMMANDE_H_INCLUDED
