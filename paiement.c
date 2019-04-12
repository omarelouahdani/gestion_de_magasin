#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paiement.h";
#include "menu.h";


paiement* CreatPaiement(int codePaiement ,  float Montant , char*  type ,Date date,vente* vente)
{
    paiement* nouv;
    nouv=(paiement*)malloc(sizeof(paiement));
    nouv->paiementCode=codePaiement;
    nouv->amount=Montant;
    nouv->type=type;
    nouv->date=date;
    nouv->vente=vente;
    return nouv;

}
ElementPaiement*  CreatElementPaiement(int codePaiement ,  float Montant , char*  type ,Date date,vente* vente)
{
    ElementPaiement* nouv;
    nouv=(ElementPaiement*)malloc(sizeof(ElementPaiement));
    nouv->paiement=CreatPaiement(codePaiement ,Montant ,type,date,vente);
    nouv->nxt=NULL;
    return nouv;
}
ElementPaiement* AjouterElementPaiement(ElementPaiement* listPaiement
                                        ,int codePaiement ,  float Montant , char*  type ,Date date ,vente* vente)
{
    ElementCommande*  nouv;
    nouv=CreatElementPaiement(codePaiement ,Montant ,type,date,vente);
    if(listPaiement==NULL)
    {
        return nouv;
    }
    else
    {
        ElementPaiement* tmp=listPaiement;
        while(tmp->nxt!=NULL)
        {
            tmp=tmp->nxt;
        }
        tmp->nxt=nouv;
    }
    return listPaiement;
}
void displayPaiement(paiement* paiement)
{
    printf(" *  code de paiement :   %d \n  ",paiement->paiementCode);
    printf(" *  Montant          :   %f \n  ",paiement->amount);
    printf(" *  le type de paiement : %s   \n ",paiement->type);
    displayDate(paiement->date);
    printf(" *  la vente :   ");
    displayVente(paiement->vente);




}
void display_list_paiement(ElementPaiement* listPaiement)
{
    printf("    \n --------------------   la liste des paiements    -------- \n  ");
    ElementPaiement*  tmp;
    int i=1;
    for(tmp=listPaiement;tmp!=NULL;tmp=tmp->nxt)
    {
        printf("--------------------------------\n ");
        printf(" * paiement : %d   ",i);
        displayPaiement(tmp->paiement);


    }
}
ElementPaiement* ajouterPaiement(ElementPaiement* listPaiement,ElementVente* listVente)
{
    int codeVente;
    printf(" -------( ajouter paiement   )------------- \n ");
    int codePaiement;
    printf("entre le code de paiement :   ");
    scanf("%d",&codePaiement);
    printf(" * choisir les ventes que vous voulez la paiement  !!!!   ");
    printf("   * voila   la liste des ventes   :   ");
    display_list_vente(listVente);
    vente*  vente=NULL;
    printf(" \n -------------------------------------------------- \n");
    printf(" *  entrez le code d'une vente  : ");
    scanf("%d",&codeVente);
    vente=RechercherVente(listVente,codeVente);

    printf("\n--------------------------------\n");
    float montant;
    printf("entrez lz montant ::  ");
    scanf("%f",&montant);
    char text[50];
    char* type;
    printf(" * saisie le type de paiement  :   ");
    scanf("%s",&text);
    type=(char*)malloc(sizeof(char)*strlen(text));
    strcpy(type,text);
    Date date;
    printf(" *  la date   :   ");
    printf(" * le jour :  ");scanf("%d",&date.jour);
    printf(" * le mois : ");scanf("%d",&date.mois);
    printf(" *  l'annee : ");scanf("%d",&date.annee);
    listPaiement=AjouterElementPaiement(listPaiement,codePaiement,montant,type,date,vente);
    return listPaiement;
}
ElementPaiement* supprimer_paiement(ElementPaiement* listPaiement,int code)
{

    if(listPaiement==NULL)
    {
        return NULL;
    }
    if(listPaiement->paiement->paiementCode==code)
    {
        ElementPaiement* tmp;
        tmp=listPaiement->nxt;
        free(listPaiement);
        tmp=supprimer_paiement(tmp,code);
        return tmp;
    }
    else
    {
        listPaiement->nxt=supprimer_paiement(listPaiement->nxt,code);
    }
    return listPaiement;
}
paiement* Rechercher_paiement(ElementPaiement* listPaiement , int code)
{
    int i=-1;
    if(listPaiement==NULL)
    {
        printf("la liste des paiementd    est vide !!!!  ");

    }
    ElementPaiement* tmp;
    for(tmp=listPaiement;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->paiement->paiementCode==code)
        {
           return tmp->paiement;
           i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n paiement  n'existe pas     !! " );
        return NULL;

    }
}
ElementPaiement* modifier_paiement(ElementPaiement* listPaiement , int code)
{
    ElementPaiement*  tmp;
    float Montant;
    char* type;
    Date date;
    char text[50];

    for(tmp=listPaiement;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->paiement->paiementCode==code)
        {
            printf(" * modification !! : \n  ");
            printf(" * modifier la vente :   ");
            tmp->paiement->vente=mainVente(tmp->paiement->vente);
            printf(" * nouveau Montant  : !! ");
            scanf("%f",&Montant);
            tmp->paiement->amount=Montant;
            printf("  *  entrez le nouveau type de paiement  :  ");
            gets(text);
            type=(char*)malloc(sizeof(char)*strlen(text));
            strcpy(type,text);
            tmp->paiement->type=type;
            printf(" \n modification de la date   :  ");
            printf(" le jour ");scanf("%d",&date.jour);
            printf("le mois : ");scanf("%d",&date.mois);
            printf("anne   :  ");scanf("%d",&date.annee);
            tmp->paiement->date=date;

        }
    }
    return listPaiement;

}
int test_list_paiement(ElementPaiement* listPaiement )
{
    if(listPaiement==NULL)return 0;
    else return 1;
}
ElementPaiement* mainPaiement(ElementPaiement* listPaiement,ElementVente* listVente)
{

    int choix;
    int code;
    paiement* paiement=NULL;

    do
    {
        printf("\n ******************  gérer les commandes   ************************   \n");
        printf(" ***    1 : Ajouter une paiement    \n ");
        printf(" ***    2 : afficher les paiements   \n ");
        printf(" ***    3 : supprimer une paiement \n ");
        printf(" ***    4 : Recherche une paiement  \n ");
        printf(" ***    5 : modifier une paiement  \n ");
        printf(" ***    6 : Registrer votre liste et retour de menu principale ****   !! \n ");
        printf(" ***    7 : quitter  \n ");
        do
        {


            printf("!!!    entrez votre choix : ");
            scanf("%d",&choix);
            if(choix<1 || choix>6) {printf(" \n votre choix doit être entre 1 et 6  !!!! ");}

        }while(choix<1 || choix>6);
        switch(choix)
        {
            case 1:
                 system("cls");
                 listPaiement=ajouterPaiement(listPaiement,listVente);break;
            case 2:
                system("cls");
                if(test_list_paiement(listPaiement))
                {
                   display_list_paiement(listPaiement);
                }
                else printf("la liste des paiements   est vide");
                break;
            case 3:
               system("cls");
               printf(" ***   \n  entrez le code du paiement  que vous voullez Supprimer  :  ");
               scanf("%d",&code);
               listPaiement=supprimer_paiement(listPaiement,code); break;
            case 4:



               system("cls");
               printf(" ***   \n  entrez le code du paiement  que vous voullez Rechercher  :  ");
               scanf("%d",&code);
               paiement=Rechercher_paiement(listPaiement,code);
               if(paiement!=NULL)
               {
                   printf(" voila les informations de la paiement trouvée !!!   :  \n  ");
                   displayPaiement(paiement);
               }

                else
                    printf("votre paiement n'existe pas dans cette base de donnée \n !!!! ");

                    break;
            case 5:
                system("cls");
                printf(" ***   \n  entrez le code du paiement  que vous voullez modifier  :  ");
               scanf("%d",&code);
                ModifierVente(listPaiement,code);

            case 6:
                system("cls");
                return listPaiement;
                mainPrincipale();


        }



    }while(choix!=5);
return listPaiement;

}

