#ifndef PAIEMENT_VENTE_H_INCLUDED
#define PAIEMENT_VENTE_H_INCLUDED
#include "vente.h";
#include "paiement.h";

typedef struct paiement_vente  paiement_vente;
struct paiement_vente
{
    vente* vente;
    ElementPaiement* listpaiement;

};
typedef struct ElementPaiementVente ElementPaiementVente;
struct ElementPaiementVente
{
    paiement_vente*  paiement_vente;
    ElementPaiementVente* nxt;

};
paiement_vente*  CreatPaiementVente(vente* vente, ElementPaiement* listpaiement);
ElementPaiementVente* CreatElementPaiementVente(vente* vente, ElementPaiement*  listpaiement);
ElementPaiementVente*  ajouterElementPaiementVente(ElementPaiementVente* listVente_paiement
                                                    , vente* vente , ElementPaiement* listpaiement);
ElementPaiementVente*  ajouterPaiementVente(ElementPaiementVente* listVente_paiement
                                            ,ElementPaiement* listpaiement,ElementVente*  listVente);

void display_Vente_Paiement(ElementPaiementVente* listVente_Paiement);
ElementPaiementVente* main_Vente_paiement(ElementPaiementVente*  listVente_paiement,
                                         ElementVente* listVente
                                         ,ElementPaiement* listpaiement);
void dispalyPaiement2(paiement* paiement);
void dispalyPaiement(ElementPaiement* listPaiement);
void display_Vente_Paiement(ElementPaiementVente* listVente_Paiement);

#endif // PAIEMENT_H_INCLUDED
