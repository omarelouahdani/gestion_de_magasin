#ifndef VENTE_H_INCLUDED
#define VENTE_H_INCLUDED
#include "produit.h";
#include "client.h";
#include "ligne_commande.h";
#include "menu.h";
typedef struct Date Date;
struct Date
{
    int jour;
    int mois;
    int annee;
};
// structre de la vente
typedef struct vente vente;
struct vente
{
    int codeVente;
    float total;
    Date date;
    ElementCommande* listCommande;
    client* client;



};
//structure de la liste des ventes ;
typedef struct ElementVente ElementVente;
struct ElementVente
{
    vente* vente;
    ElementVente* nxt;
};

vente* creatVente(int codeVente , Date date , ElementCommande*  listCommande ,client* client);
double somTotal(ElementCommande* listCommande);
ElementVente* CreatElementVente(int codeVente ,  Date date
                                , ElementCommande* listCommande , client* client);
ElementVente* ajouterElementVente(ElementVente* listVente , int codeVente,  Date date
                                  , ElementCommande* listCommande , client* client);
void displayDate(Date date);
void displayVente(vente* vente);
void display_list_vente(ElementVente* listVente );
ElementVente* mainVente(ElementVente*  listvente);
client* creerclient();
ElementVente*  ajouterVente(ElementCommande*  listVente);
ElementVente* SupprimerVente(ElementVente* listVente,int codeVente);
vente* RechercherVente(ElementVente* listVente,int codeVente);

#endif // VENTE_H_INCLUDED
