#ifndef PAIEMENT_H_INCLUDED
#define PAIEMENT_H_INCLUDED
#include "client.h";
#include "produit.h";
#include "ligne_commande.h";
#include "menu.h";
#include "vente.h";
typedef struct paiement paiement;
struct paiement
{
    int paiementCode;
    float amount;
    char *type;
    Date date;
    vente* vente;




};
typedef struct ElementPaiement ElementPaiement;
struct ElementPaiement
{
    paiement* paiement;
    ElementPaiement* nxt;

};
paiement* CreatPaiement(int codePaiement ,  float Montant , char*  type ,Date date,vente* vente);

ElementPaiement*  CreatElementPaiement(int codePaiement ,  float Montant , char*  type,Date date,vente* vente);
ElementPaiement* AjouterElementPaiement(ElementPaiement* listPaiement,int codePaiement ,  float Montant
                                         , char*  type ,Date date,vente* vente );
void displayPaiement(paiement* paiement);
ElementPaiement* ajouterPaiement(ElementPaiement* listPaiement,ElementVente* listVente);
ElementPaiement* supprimer_paiement(ElementPaiement* listPaiement,int code);
paiement* Rechercher_paiement(ElementPaiement* listPaiement , int code);
ElementPaiement* modifier_paiement(ElementPaiement* listPaiement , int code);
int test_list_paiement(ElementPaiement* listPaiement );
ElementPaiement* mainPaiement(ElementPaiement* listPaiement,ElementVente* listVente);
void display_list_paiement(ElementPaiement* listPaiement);
#endif // PAIEMENT_H_INCLUDED
