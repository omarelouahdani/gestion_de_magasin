#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ligne_commande.h";
#include "client.h";
#include "produit.h";

ligne_commande* Creat_ligne_commande(produit* produit ,int quantite,int ID_Cmd)
{

    ligne_commande* nouv;
    nouv=(ligne_commande*)malloc(sizeof(ligne_commande));
    nouv->produit=produit;

    nouv->quantite=quantite;
    nouv->ID_Cmd=ID_Cmd;
    nouv->subTotal=quantite*produit->price;

    return nouv;


}

ElementCommande* CreatElementCommande(produit* produit,int quantite,int ID_Cmd )
{
    ElementCommande* nouvCommande;
    nouvCommande=(ElementCommande*)malloc(sizeof(ElementCommande));
    nouvCommande->ligne_commande=Creat_ligne_commande(produit,quantite,ID_Cmd);
    nouvCommande->nxt=NULL;
}
ElementCommande* ajouterCommandeElement(ElementCommande* listCommande , produit* produit,int quantite,int ID_Cmd)
{
    ElementCommande* nouv;
    nouv=CreatElementCommande(produit,quantite,ID_Cmd);
    if(listCommande==NULL)
    {
        return nouv;
    }
    ElementCommande* tmp=listCommande;
    while(tmp->nxt!=NULL)
    {
        tmp=tmp->nxt;
    }
    tmp->nxt=nouv;
    return listCommande;
}
void display_ligne_commande(ligne_commande*  commande)
{

        printf("  *             identification  :    %d  : \n ",commande->ID_Cmd);
        printf("  *             quantite : %d  \n ",commande->quantite);
        printf("  *             subTotal : %f  \n ",commande->subTotal);
        printf("*******************               ********************** \n");
        displayProduit(commande->produit);
}
void display_liste_commande(ElementCommande* listCommande)
{
    printf("     ----------------      les lignes Commandes --------------  \n ");
    ElementCommande* tmp;
    int i=1;

    for(tmp=listCommande;tmp!=NULL;tmp=tmp->nxt)
    {
        printf("\n -----------------------------------------------------\n ");
        printf("  \n  *             commande : %d           \n ",i);
        display_ligne_commande(tmp->ligne_commande);
        i++;
        printf("\n -----------------------------------------------------\n ");
    }
}

int test_list_commande(ElementCommande* listCommande)
{
    if(listCommande==NULL) return 0;
    else return 1;
}
ElementCommande* ajouterCommande(ElementCommande* listCommande)
{
    printf("----------------- ajouter ligne Commande ----------------------- \n  ");
    printf("-------------------------------------------------------------------\n");
    printf("-------------------- 2: choisis un produit -----------------------------");
    ProduitElement* listProduit=NULL;
    listProduit=getProduit(listProduit);
    display_liste_produit(listProduit);
    produit* produit;
    int code;
    do {
    printf(" entrez le code de produit que vous voulez ajouter  :: \n ");
    scanf("%d",&code);
    produit=Recherche_ligne_de_commande(listProduit,code);
    if(produit==NULL)
    {
        printf("*****           tu dois choisis un produit qui existe dans la base de donné !!!!!   \n  ");
    }
    }while(produit==NULL);
    int quantite;
    int ID_Cmd;
    printf(" saisis l'identification de la ligne de commande !! :  ");
    scanf("%d",&ID_Cmd);
    printf("entrez la quantite   !!   : ");
    scanf("%d",&quantite);
    listCommande=ajouterCommandeElement(listCommande,produit,quantite,ID_Cmd);
    return listCommande;
}
ElementCommande* supprimer_ligne_de_commande(ElementCommande* listCommande,int code)
{

    if(listCommande==NULL)
    {
        return NULL;
    }
    if(listCommande->ligne_commande->ID_Cmd==code)
    {
        ElementCommande* tmp;
        tmp=listCommande->nxt;
        free(listCommande);
        tmp=supprimer_ligne_de_commande(tmp,code);
        return tmp;
    }
    else
    {
        listCommande->nxt=supprimer_ligne_de_commande(listCommande->nxt,code);
    }
    return listCommande;
}
ligne_commande* Recherche_ligne_de_commande(ElementCommande* listCommande , int code)
{
    int i=-1;
    if(listCommande==NULL)
    {
        printf("la liste des commandes   est vide !!!!  ");

    }
    ElementCommande* tmp;
    for(tmp=listCommande;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->ligne_commande->ID_Cmd==code)
        {
           return tmp->ligne_commande;
           i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n commande  n'existe pas     !! " );
        return NULL;

    }
}
ElementCommande* modifier_commande(ElementCommande* listCommande , int code)
{
    ElementCommande*  tmp;
    int quantite;
    int codeProduit;
    float subtotal;
    ProduitElement* listProduit=NULL;
    for(tmp=listCommande;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->ligne_commande->ID_Cmd==code)
        {
            printf(" * modification !! : \n");
            printf(" * quantite   :  ");
            scanf("%d",&quantite);
            tmp->ligne_commande->quantite=quantite;
            codeProduit=tmp->ligne_commande->produit->code;
            listProduit=ajouterProduitElement(listProduit,tmp->ligne_commande->produit);
            listProduit=ModifierProduit(listProduit,codeProduit);

            tmp->ligne_commande->produit=listProduit->produit;
            subtotal=quantite*tmp->ligne_commande->produit->price;
            tmp->ligne_commande->subTotal=subtotal;

        }
    }
    return listCommande;

}
ElementCommande*  getCommande(ElementCommande  *listCommande)
{
    FILE *fichier=NULL;
    int ID,quantite;
    double subTotal;
    //produit
    produit* nouvProduit;
    int code2;
    char text_desig[50];
    float prix;
    char *designation;
    fichier = fopen("bd_commande.txt","r");
      if (fichier != NULL)
    {
        while(!feof(fichier))
        {
            fscanf(fichier,"%d %d %f %d %s %f %d %s %s %s\n"
            ,&ID,&quantite,&subTotal,&code2,&text_desig,&prix);
            designation=(char*)malloc(sizeof(char)*strlen(text_desig));
            strcpy(designation,text_desig);
            nouvProduit=createProduct(code2,designation,prix);
            listCommande=ajouterCommandeElement(listCommande,nouvProduit,quantite,ID);

        }
        return listCommande;
        // On peut lire et écrire dans le fichier
    }
    else
    {

        return NULL;
    }
    fclose(fichier);
}
void bd_commane(ElementCommande* listCommande)
{
    FILE *fichier=NULL;
    ElementCommande* tmp;
    fichier = fopen("bd_commande.txt", "w");
      if (fichier != NULL)
    {
        for(tmp=listCommande;tmp!=NULL;tmp=tmp->nxt)
        {
            fprintf(fichier," %d \t %d \t %f \t  %d \t %s \t %f   \n"
                    ,tmp->ligne_commande->ID_Cmd,tmp->ligne_commande->quantite
                    ,tmp->ligne_commande->subTotal
                    ,tmp->ligne_commande->produit->code,tmp->ligne_commande->produit->designation
                    ,tmp->ligne_commande->produit->price);
        }
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier bd_commande.txt");
        return ;
    }
    fclose(fichier);
}

ElementCommande* mainCommande(ElementCommande* listCmd)
{
    ElementCommande* listCommande=listCmd;
    int choix;
    int code;
    ligne_commande* commande=NULL;

    do
    {
        printf("\n ******************  gérer les commandes   ************************   \n");
        printf(" ***    1 : Ajouter une commande    \n ");
        printf(" ***    2 : afficher les commande   \n ");
        printf(" ***    3 : supprimer une commande \n ");
        printf(" ***    4 : Recherche une commande  \n ");
        printf(" ***    5 : Modifier une commande   !! \n ");
        printf(" ***    6 : quitter  \n ");
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
                 listCommande=ajouterCommande(listCommande);break;
            case 2:
                system("cls");
                if(test_list_commande(listCommande))
                {
                   display_liste_commande(listCommande);
                }
                else printf("la liste des commandes  est vide");
                break;
            case 3:
               system("cls");
               printf(" ***   \n  entrez le code du commande  que vous voullez Supprimer  :  ");
               scanf("%d",&code);
               listCommande=supprimer_ligne_de_commande(listCommande,code); break;
            case 4:
            system("cls");
               printf(" ***   \n  entrez le code du commande que vous voullez Rechercher  :  ");
               scanf("%d",&code);
               commande=Recherche_ligne_de_commande(listCommande,code);
               if(commande!=NULL)
               {
                   printf(" voila les informations de la commande trouvée !!!   :  \n  ");
                   display_ligne_commande(commande);
               }

                else
                    printf("votre commande n'existe pas dans cette base de donnée \n !!!! ");

                    break;
            case 5:
               system("cls");
               printf(" ***   \n  entrez le code du commande que vous voullez Modifier   :  ");
               scanf("%d",&code);
               listCommande=modifier_commande(listCommande,code);break;



        }



    }while(choix!=5);

return listCommande;
}
