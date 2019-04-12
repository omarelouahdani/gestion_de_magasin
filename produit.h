#ifndef PRODUIT_H_INCLUDED
#define PRODUIT_H_INCLUDED


typedef struct produit produit;
struct produit
{
    int code;
    char *designation;
    float price;

};
typedef struct ProduitElement ProduitElement;
struct ProduitElement
{
    produit *produit;
    ProduitElement *nxt;
};
produit* createProduct (int code ,char* designation ,float prix);
ProduitElement *CreatProduitElement(produit *product);
ProduitElement* ajouterProduitElement(ProduitElement*  listProduit , produit* produit);
void displayProduit(produit *prd);
void  display_liste_produit(ProduitElement* listProduit);
int test_liste_produit(ProduitElement *ListProduit);
char* saisieDesignation();
ProduitElement* ajouterProduit(ProduitElement* listProduit);
ProduitElement* supprimerProduits(ProduitElement* listProduit,int code);
produit* RechercherProduit(ProduitElement* listProduit , int code);
ProduitElement* ModifierProduit(listProduits,code);
ProduitElement*  getProduit(ProduitElement  *list_produit);
void bd_produit(ProduitElement* list_produit);
void mainProduit();
#endif // PRODUIT_H_INCLUDED
