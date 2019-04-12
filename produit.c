#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produit.h";
typedef struct produit produit;

produit* createProduct (int code ,char* designation ,float prix)
{
    char txt[20];
    produit *prd;
    prd=(produit*)malloc(sizeof(produit));
    prd->code=code;
    prd->designation=designation;
    prd->price=prix;
    return prd;

}
ProduitElement *CreatProduitElement(produit *product)
{
    ProduitElement *nouvProduit;
    nouvProduit=(ProduitElement*)malloc(sizeof(ProduitElement));
    nouvProduit->produit=product;
    nouvProduit->nxt=NULL;
    return nouvProduit;


}
ProduitElement* ajouterProduitElement(ProduitElement*  listProduit , produit* produit)
{
    ProduitElement* nouv;
    nouv=CreatProduitElement(produit);
    if(listProduit==NULL)
    {
        return nouv;
    }
    ProduitElement* tmp=listProduit;
    while(tmp->nxt!=NULL)
    {
        tmp=tmp->nxt;
    }
    tmp->nxt=nouv;
    return listProduit;
}
void displayProduit(produit *prd)
{
        printf("---------   les informations du produit  --------------------\n ");
        printf("\n * code : %d \n",prd->code);
        printf("\n * designation : %s \n",prd->designation);
        printf(" \n* prix :         %f \n",prd->price);

}
void display_liste_produit(ProduitElement* listProduit)
{
    printf("\n ------------------------   la liste des produits    ----------------------- \n");
    ProduitElement* tmp;
    int i=1;
    for(tmp=listProduit;tmp!=NULL;tmp=tmp->nxt)
    {
        printf(" \n * produit : %d  \n\n  ",i);
        displayProduit(tmp->produit);
        i++;


    }
}
int test_liste_produit(ProduitElement *ListProduit)
{
    if(ListProduit==NULL) return 0;
    else return 1;

}
char* saisieDesignation()
{
    char txt[50];
    char* exp;
    printf(" \ * entrez la designation du prouit :   ");
    scanf("%s",txt);
    exp=(char*)malloc(sizeof(char)*strlen(txt));
    strcpy(exp,txt);
    return exp;

}
ProduitElement* ajouterProduit(ProduitElement* listProduit)
{
    produit *prd;
    int code;
    float prix;
    char* designation;
    printf("  le code :  ");
    scanf("%d",&code);

    printf("designation : \n ");
    designation=saisieDesignation();
    printf("  prix :  ");
    scanf("%f",&prix);

    prd=createProduct(code,designation,prix);
    listProduit=ajouterProduitElement(listProduit,prd);
    return listProduit;
}
ProduitElement* supprimerProduits(ProduitElement* listProduit,int code)
{

    if(listProduit==NULL)
    {
        return NULL;
    }
    if(listProduit->produit->code==code)
    {
        ProduitElement* tmp;
        tmp=listProduit->nxt;
        free(listProduit);
        tmp=supprimerProduits(tmp,code);
        return tmp;
    }
    else
    {
        listProduit->nxt=supprimerProduits(listProduit->nxt,code);
    }
    return listProduit;
}
produit* RechercherProduit(ProduitElement* listProduit , int code)
{
    int i=-1;
    if(listProduit==NULL)
    {
        printf("la liste des produits  est vide !!!!  ");
    }
    ProduitElement* tmp;
    for(tmp=listProduit;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->produit->code==code)
        {
           return tmp->produit;
        }
    }
    if(i==-1)
    {
        printf(" \n le produits n'existe pas     !! " );
        return  NULL;
    }

}
ProduitElement* ModifierProduit(listProduits,code)
{
    int i=-1;
    char* designation;
    float prix;
    if(listProduits==NULL)
    {
        printf("la liste des produits   est vide !!!!  ");
    }
    ProduitElement* tmp;
    for(tmp=listProduits;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->produit->code==code)
        {
            printf("\n le produit  existe !! voous pouvez le  modifier !!! \n  ");
            printf(" nouveau designation : ");
            designation=saisieDesignation();
            printf(" prix  : ");
        scanf("%f",&prix);
           tmp->produit->designation=designation;
           tmp->produit->price=prix;
            i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n le produit n'existe pas pour modifier      !! " );

    }
    return listProduits;
}
ProduitElement*  getProduit(ProduitElement  *list_produit)
{
    FILE *fichier=NULL;
    produit* nouv;
    int code;
    char text_desig[50];
    float prix;
    char *designation;
    fichier = fopen("bd_produitt.txt","r");
      if (fichier != NULL)
    {
        while(!feof(fichier))
        {
            fscanf(fichier,"%d %s %f\n",&code,&text_desig,&prix);
            designation=(char*)malloc(sizeof(char)*strlen(text_desig));
            strcpy(designation,text_desig);
            nouv=createProduct(code,designation,prix);
            list_produit=ajouterProduitElement(list_produit,nouv);
        }
        return list_produit;
        // On peut lire et écrire dans le fichier
    }
    else return NULL;
    fclose(fichier);
}
void bd_produit(ProduitElement* list_produit)
{
    FILE *fichier=NULL;

    ProduitElement* tmp;
    fichier = fopen("bd_produitt.txt","w");
      if (fichier != NULL)
    {
        for(tmp=list_produit;tmp!=NULL;tmp=tmp->nxt)
        {
            fprintf(fichier,"%d \t %s \t %f \n",tmp->produit->code
                    ,tmp->produit->designation,tmp->produit->price);
        }

    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier bd_produit.txt");
        return ;
    }
    fclose(fichier);
}

void mainProduit()
{
    ProduitElement* ListProduits;
    ListProduits=NULL;
    ListProduits=getProduit(ListProduits);
    int choix;
    int code;
    produit*  produit=NULL;
    do
    {
        printf("\n ******************     Le menu  ************************   \n");
        printf(" ***    1 : Ajouter un produits dans la liste des produits  \n ");
        printf(" ***    2 : afficher La liste des produits   \n ");
        printf(" ***    3 : supprimer un produits  \n ");
        printf(" ***    4 : Recherche un produit  \n ");
        printf(" ***    5 : Modifier un  produit   \n ");
        printf(" ***    6 : Menu principale   \n ");
        printf(" ***    7 : quitter  \n ");
        do
        {


            printf("!!!    entrez votre choix : ");
            scanf("%d",&choix);
            if(choix<1 || choix>7) {printf(" \n votre choix doit être entre 1 et 7 !!!! ");}

        }while(choix<1 || choix>7);
        switch(choix)
        {
            case 1:
                system("cls");
                ListProduits=ajouterProduit(ListProduits);break;
            case 2:
                system("cls");
                if(test_liste_produit(ListProduits))
                {
                    display_liste_produit(ListProduits);
                }
                else printf("la liste des produits est vide");
                break;
            case 3:
                system("cls");

               printf(" ***   \n  entrez le code du produit que vous voullez Supprimer  :  ");
               scanf("%d",&code);

                 ListProduits=supprimerProduits(ListProduits,code); break;
            case 4:
               system("cls");
               printf(" ***   \n  entrez le code du produit que vous voullez Rechercher  :  ");
               scanf("%d",&code);
                produit=RechercherProduit(ListProduits,code);
                if(produit==NULL)
                {
                    printf(" essaye de choisis un produit qui existe dans base de donnée !!! \n ");
                }
                else
                {
                    printf("voila le produit :  \n ");
                    displayProduit(produit);
                }
                 break;;
            case 5 :
               system("cls");
               printf(" ***   \n  entrez le code du produit que vous voullez Modifier  :  ");
               scanf("%d",&code);

                ModifierProduit(ListProduits,code); break;
            case 6 : system("cls");
                     mainPrincipale();
                     break;
        }
    }while(choix!=7);
    bd_produit(ListProduits);

}
