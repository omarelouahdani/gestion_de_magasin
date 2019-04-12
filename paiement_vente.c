#include <stdio.h>
#include <stdlib.h>
#include "menu.h";
#include "paiement_vente.h";

paiement_vente*  CreatPaiementVente(vente* vente, ElementPaiement* listpaiement)
{
    paiement_vente* nouv;
    nouv=(paiement_vente*)malloc(sizeof(paiement_vente));
    nouv->vente=vente;
    nouv->listpaiement=listpaiement;
    return nouv;
};
ElementPaiementVente* CreatElementPaiementVente(vente* vente, ElementPaiement*  listpaiement)
{
    ElementPaiementVente* nouv;
    nouv=(ElementPaiementVente*)malloc(sizeof(ElementPaiementVente));
    nouv->paiement_vente=CreatPaiementVente(vente,listpaiement);
    nouv->nxt=NULL;
    return nouv;
}
ElementPaiementVente*  ajouterElementPaiementVente(ElementPaiementVente* listVente_paiement , vente* vente , ElementPaiement* listpaiement)
{
    ElementPaiementVente*  nouv;
    nouv=CreatElementPaiementVente(vente,listpaiement);
    if(listVente_paiement==NULL) return nouv;
    else
    {
        ElementPaiementVente* tmp=listVente_paiement;
        while(tmp->nxt!=NULL)
        {
            tmp=tmp->nxt;
        }
        tmp->nxt=nouv;
    }
    return listVente_paiement;
}
ElementPaiementVente*  ajouterPaiementVente(ElementPaiementVente* listVente_paiement
                                            ,ElementPaiement* listpaiement,ElementVente*  listVente)
{
    ElementVente* tmpVente;
    ElementPaiement* tmpPaiement;
    vente* vente;

    for(tmpVente=listVente;tmpVente!=NULL;tmpVente=tmpVente->nxt)
    {
        vente=tmpVente->vente;
        ElementPaiement* listPmt=NULL;
        for(tmpPaiement=listpaiement;tmpPaiement!=NULL;tmpPaiement=tmpPaiement->nxt)
    {
        if(tmpPaiement->paiement->vente->codeVente==tmpVente->vente->codeVente)
        {
            listPmt=AjouterElementPaiement(listPmt,tmpPaiement->paiement->paiementCode,
                                           tmpPaiement->paiement->amount,tmpPaiement->paiement->type
                                           ,tmpPaiement->paiement->date,tmpPaiement->paiement->vente);

        }
    }
    listVente_paiement=ajouterElementPaiementVente(listVente_paiement,vente,listPmt);
    }
    return listVente_paiement;


}
void dispalyPaiement2(paiement* paiement)
{
    printf(" *  code de paiement :   %d \n  ",paiement->paiementCode);
    printf(" *  Montant          :   %f \n  ",paiement->amount);
    printf(" *  le type de paiement : %s   \n ",paiement->type);
    displayDate(paiement->date);

}
void dispalyPaiement(ElementPaiement* listpaiement)
{
      printf("    \n --------------------   la liste des paiements    -------- \n  ");
    ElementPaiement*  tmp;
    int i=1;
    for(tmp=listpaiement;tmp!=NULL;tmp=tmp->nxt)
    {
        printf("--------------------------------\n ");
        printf(" * paiement : %d   ",i);
        dispalyPaiement2(tmp->paiement);


    }
}
void display_Vente_Paiement(ElementPaiementVente* listVente_Paiement)
{
    printf(" \n----------------( affichage )--------------------\n");
    ElementPaiementVente* tmp;
    int i=1;
    for(tmp=listVente_Paiement;tmp!=NULL;tmp=tmp->nxt)
    {
        printf("   * vente : %d ",i);
        displayVente(tmp->paiement_vente->vente);
        printf("   * Les paiements  : \n ");
        dispalyPaiement(tmp->paiement_vente->listpaiement);

    }
}
ElementPaiementVente* main_Vente_paiement(ElementPaiementVente*  listVente_paiement,
                                         ElementVente* listVente
                                         ,ElementPaiement* listpaiement)
{
    listVente_paiement=ajouterPaiementVente(listVente_paiement,listpaiement,listVente);
    display_Vente_Paiement(listVente_paiement);
    return listVente_paiement;

}



