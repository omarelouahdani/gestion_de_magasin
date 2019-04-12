#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne_commande.h";
#include "client.h";
#include "produit.h";
#include "vente.h";


vente* creatVente(int codeVente , Date date , ElementCommande*  listCommande ,client* client
                  )
{
    vente* nouvVente;
    nouvVente=(vente*)malloc(sizeof(vente));
    nouvVente->codeVente=codeVente;
    nouvVente->total=somTotal(listCommande);
    nouvVente->date=date;
    nouvVente->listCommande=listCommande;
    nouvVente->client=client;


    return nouvVente;

}
double somTotal(ElementCommande* listCommande)
{
    ElementCommande* tmp;
    double som=0;
    for(tmp=listCommande;tmp!=NULL;tmp=tmp->nxt)
    {
        som=som+tmp->ligne_commande->subTotal;
    }
    return som;
}
ElementVente* CreatElementVente(int codeVente ,  Date date , ElementCommande* listCommande , client* client
                                )
{
    ElementVente* nouv;
    nouv=(ElementCommande*)malloc(sizeof(ElementVente));
    nouv->vente=creatVente(codeVente ,date ,listCommande ,client);
    nouv->nxt=NULL;
    return nouv;
}
ElementVente* ajouterElementVente(ElementVente* listVente , int codeVente ,  Date date
                                  , ElementCommande* listCommande , client* client
                                  )
{
    ElementCommande* nouv;
    nouv=CreatElementVente(codeVente ,date ,listCommande ,client);
    if(listVente==NULL) return nouv;
    else
    {
        ElementVente*  tmp=listVente;
        while(tmp->nxt!=NULL)
        {
            tmp=tmp->nxt;
        }
        tmp->nxt=nouv;
        return listVente;
    }
}
void displayDate(Date date)
{
    printf("*La date :  %d/%d/%d  \n",date.jour,date.mois,date.annee);
}
void displayVente(vente* vente)
{
    printf("            * code de la vente  : %d  \n",vente->codeVente);
    printf("            * Total :    %f \n  ",vente->total);
    displayDate(vente->date);
    displayClient(vente->client);
    printf(" ------(    les commandes concernant ce client :   )----------_\n");
    if(test_list_commande(vente->listCommande))
    {
    display_liste_commande(vente->listCommande);}
    else printf(" la liste des commandes est vide ");


}
void display_list_vente(ElementVente* listVente )
{
    printf("\n -------------  la liste des  ventes   ---------------------- \n");
    ElementVente* tmp;
    int i=1;
    for(tmp=listVente;tmp!=NULL;tmp=tmp->nxt)
    {
        printf("---------------------------------------------------------------");
        printf("\n----------------       *vente : %d  --------------------\n ",i);

        displayVente(tmp->vente);
        printf("\n ");

    }
}

ElementVente*  ajouterVente(ElementCommande*  listVente)
{
    int codeVente;
    printf(" ----    entrer le code de vente  :  \n  ");
    scanf("%d",&codeVente);

    printf(" -----------------    choisis un client de la liste des client -----   ! \n");
    client* client=NULL;
    int code;
    ClientElement* listClient=NULL;
    listClient=getclient(listClient);
    display_liste_client(listClient);
    printf("entrez le code de client que vous voulez ajouter  !! : ");
    scanf("%d",&code);
    client=RechercherClient(listClient,code);

    printf("------------   demander les commandes     ------  \n");
    ElementCommande* listCommande=NULL;
    int choix;
    do
    {
        printf(" * 1  :  ajouter un commande  \n ");
        printf(" * 2  :  enregistrer          \n ");
        printf("----------------------------------\n");
        printf("  entrez votre choix : ");
        scanf("%d",&choix);
        switch(choix)
        {
        case 1: listCommande=ajouterCommande(listCommande);

        }

    }while(choix!=2);

    printf("-------------     saisie la date  de cette vente : --------------- \n");
    int jour,mois,annee;
    printf("le jour : ");
    scanf("%d",&jour);
    printf("le mois : ");
    scanf("%d",&mois);
    printf("le annee : ");
    scanf("%d",&annee);
    Date date;
    date.jour=jour; date.mois=mois; date.annee=annee;
    listVente=ajouterElementVente(listVente,codeVente,date,listCommande,client);
}
ElementVente* SupprimerVente(ElementVente* listVente,int codeVente)
{
    if(listVente==NULL)return NULL;
    if(listVente->vente->codeVente==codeVente)
    {
        ElementVente* tmp;
        tmp=listVente->nxt;
        free(listVente);
        tmp=SupprimerVente(tmp,codeVente);
        return tmp;
    }
    else
    {
        listVente->nxt=SupprimerVente(listVente->nxt,codeVente);
    }
    return listVente;

}
vente* RechercherVente(ElementVente* listVente,int codeVente)
{
    int i=-1;
    if(listVente==NULL)
    {
        printf("la liste des ventes   est vide !!!!  ");

    }
    ElementVente* tmp;
    for(tmp=listVente;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->vente->codeVente==codeVente)
        {
           return tmp->vente;
           i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n vente  n'existe pas     !! " );
        return NULL;

    }
}
int test_liste_vente(ElementVente* listVente)
{
    if(listVente==NULL) return 0;
    else return 1;
}
ElementVente* ModifierVente(ElementVente*  listVente , int code)
{   int codeVente;
    Date date;
    int jour;int mois;int annee;
    ElementVente* tmp;
    for(tmp=listVente;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->vente->codeVente==code)
        {
            printf("entrez nouveau code de cette vente  :  ");
            scanf("%d",&codeVente);
            tmp->vente->codeVente=codeVente;
            printf(" *  modifier la date : ");
            printf(" le jour :  ");
            scanf("%d",&jour);
            printf("le mois :  ");
            scanf("%d",&mois);
            printf("annee :  ");
            scanf("%d",&annee);
            date.jour=jour;date.mois=mois;date.annee=annee;
            tmp->vente->date=date;
            printf("........................................");
            printf(" * modifier le  client  !  : \n ");
            printf(" *****   choisis un nouveau client   :    \n ");
            ClientElement* listClient=NULL;
            client* client;
            listClient=getclient(listClient);
            display_liste_client(listClient);
            int code;
            printf("entrez le code de client que vous voulez ajouter  !! : ");
            scanf("%d",&code);
            client=RechercherClient(listClient,code);
            tmp->vente->client=client;
            printf("-----------------------------------------------------------\n");
            printf(" *  modifier la liste de commande concernant  ce client  :   \   ");
            tmp->vente->listCommande=mainCommande(tmp->vente->listCommande);
            printf(" \n votre vente à été modifier avec succés    !!!!        \n  ");



        }
    }
    return listVente;
}
ElementVente* mainVente(ElementVente*  listvente){


    ElementVente* listVente=listvente;
    int choix;
    int code;
    vente* vente=NULL;

    do
    {
        printf("\n ******************   les ventes   ************************   \n");
        printf(" ***    1 : Ajouter une vente    \n ");
        printf(" ***    2 : afficher les ventes   \n ");
        printf(" ***    3 : supprimer une ventes \n ");
        printf(" ***    4 : Recherche une une vente  \n ");
        printf(" ***    5 : Modifier une vente       \n ");
        printf(" ***    6 : menu Principlae       ****   !! \n ");
        printf(" ***    7 : quitter  \n ");
        do
        {


            printf("!!!    entrez votre choix : ");
            scanf("%d",&choix);
            if(choix<1 || choix>7) {printf(" \n votre choix doit être entre 1 et 7  !!!! ");}

        }while(choix<1 || choix>7);
        switch(choix)
        {
            case 1:
                 system("cls");
                 listVente=ajouterVente(listVente);break;
            case 2:
                system("cls");
                if(test_liste_vente(listVente))
                {
                   display_list_vente(listVente);
                }
                else printf("la liste des ventes  est vide");
                break;
            case 3:
               system("cls");
               printf(" ***   \n  entrez le code du vente  que vous voullez Supprimer  :  ");
               scanf("%d",&code);
               listVente=SupprimerVente(listVente,code); break;
            case 4:

               system("cls");
               printf(" ***   \n  entrez le code du vente que vous voullez Rechercher  :  ");
               scanf("%d",&code);
               vente=RechercherVente(listVente,code);
               if(vente!=NULL)
               {
                   printf(" voila les informations de la vente trouvée !!!   :  \n  ");
                   displayVente(vente);
               }

                else
                    printf("votre vente n'existe pas dans cette base de donnée \n !!!! ");

                    break;
            case 5:
                 system("cls");
               printf(" ***   \n  entrez le code du vente que vous voullez modifier  :  ");
               scanf("%d",&code);
               listVente=ModifierVente(listVente,code);
            case 6:

               system("cls");
                return listVente;
                mainPrincipale();


        }



    }while(choix!=7);
    return listVente;




}

