#include <stdio.h>
#include <stdlib.h>
#include "client.h";
#include "produit.h";
#include "vente.h";
#include "menu.h";
#include "paiement.h";
#include "ligne_commande.h";
#include "paiement_vente.h";
static  ElementPaiement* listPaiement=NULL;
static   ElementCommande* listCommande=NULL;
static    ElementVente* listVente=NULL;
static ElementPaiementVente* listVente_Paiement=NULL;
void mainPrincipale(){
    int choix;

    do
    {
        printf("----------------------------------------------------------------------------\n");
        printf("------------------------------     la gestion de magasin   ------------------\n ");
        printf("----------------  *   1 : client                           \n");
        printf("----------------  *   2 : produit                          \n");
        printf("----------------  *   3 : Les ventes                \n");
        printf("----------------  *   4 : Les paiements                \n");
        printf("----------------  *   5 : les ventes et les paiements                 \n");
        printf("----------------  *   6 : quitter                           \n ");
        printf("----------------------------------------------------------------------------\n");
        do
        {
              printf("  entrez votre choix :       ");
              scanf("%d",&choix);

        }while(choix<1 || choix>6);
        switch(choix)
        {
            case 1 : system("cls");
                      mainClient();
                      break;
            case 2:
                      system("cls");
                      mainProduit();
                      break;
            case 3:
                      system("cls");
                      listVente=mainVente(listVente);
                      break;
            case 4:
                system("cls");
                listPaiement=mainPaiement(listPaiement,listVente);
                break;
            case 5:
                system("cls");
                listVente_Paiement=main_Vente_paiement(listVente_Paiement,listVente,listPaiement);
                break;

        }
    }while(choix!=6);

}
