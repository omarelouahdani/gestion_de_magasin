#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h";
#include "menu.h";
client* createClient (int code ,char* nom ,char *prenom ,char *telephone)
{

    client *nouvClient;
    nouvClient=(client*)malloc(sizeof(client));
    nouvClient->code=code;
    nouvClient->nom=nom;
    nouvClient->prenom=prenom;
    nouvClient->telephone=telephone;
    return nouvClient;

}
ClientElement *CreatClientElement(client *client)
{
    ClientElement *nouvClient;
    nouvClient=(ClientElement*)malloc(sizeof(ClientElement));
    nouvClient->client=client;
    nouvClient->nxt=NULL;
    return nouvClient;


}
ClientElement* ajouterClientElement(ClientElement*  listClient , client* client)
{
    ClientElement* nouv;
    nouv=CreatClientElement(client);
    if(listClient==NULL)
    {
        return nouv;
    }
    ClientElement* tmp=listClient;
    while(tmp->nxt!=NULL)
    {
        tmp=tmp->nxt;
    }
    tmp->nxt=nouv;
    return listClient;
}
void displayClient(client *client)
{


        printf("---------   les informations du client  --------------------\n ");
        printf("\n * code : %d \n",client->code);
        printf("\n * nom  : %s \n",client->nom);
        printf("\n * prenom  : %s \n",client->prenom);
        printf(" \n* telephone  :         %s \n",client->telephone);

}
void display_liste_client(ClientElement* listClient)
{
    printf("\n ------------------------   la liste des clients     ----------------------- \n");
    ClientElement* tmp;
    int i=1;
    for(tmp=listClient;tmp!=NULL;tmp=tmp->nxt)
    {
        printf(" \n * client : %d  \n\n  ",i);
        displayClient(tmp->client);
        i++;


    }
}
int test_liste_client(ClientElement *listClient)
{
    if(listClient==NULL) return 0;
    else return 1;

}
char* saisietxt()
{
    char txt[50];
    char* exp;
    scanf("%s",txt);
    exp=(char*)malloc(sizeof(char)*strlen(txt));
    strcpy(exp,txt);
    return exp;

}
ClientElement* ajouterClient(ClientElement* listClient)
{
    client *client;
    int code;
    char* telephone;
    char* nom;
    char* prenom;
    printf("  le code :  ");
    scanf("%d",&code);
    printf(" nom :  ");
    nom=saisietxt();
    printf("prenom : ");
    prenom=saisietxt();
    printf("telephone  : \n ");
    telephone=saisietxt();
    client=createClient(code,nom,prenom,telephone);
    listClient=ajouterClientElement(listClient,client);
    return listClient;
}
ClientElement* supprimerClient(ClientElement* listClient,int code)
{

    if(listClient==NULL)
    {
        return NULL;
    }
    if(listClient->client->code==code)
    {
        ClientElement* tmp;
        tmp=listClient->nxt;
        free(listClient);
        tmp=supprimerClient(tmp,code);
        return tmp;
    }
    else
    {
        listClient->nxt=supprimerClient(listClient->nxt,code);
    }
    return listClient;
}
client* RechercherClient(ClientElement* listClient , int code)
{
    int i=-1;
    if(listClient==NULL)
    {
        printf("la liste des Clients   est vide !!!!  ");

    }
    ClientElement* tmp;
    for(tmp=listClient;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->client->code==code)
        {
           return tmp->client;
           i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n le client n'existe pas     !! " );
        return NULL;

    }
}
ClientElement* ModifierClient(ClientElement* listClient,int code)
{
    int i=-1;

    char* telephone;
    char* nom;
    char* prenom;

    if(listClient==NULL)
    {
        printf("la liste des Clients   est vide !!!!  ");

    }
    ClientElement* tmp;
    for(tmp=listClient;tmp!=NULL;tmp=tmp->nxt)
    {
        if(tmp->client->code==code)
        {
            printf("\n le client  existe !! voous pouvez modifier !!! \n  ");
            printf(" nouveau nom : ");
           nom=saisietxt();
           printf(" prenom  : ");
           prenom=saisietxt();
           printf(" telephone  : ");
           telephone=saisietxt();
           tmp->client->nom=nom;
           tmp->client->prenom=prenom;
           tmp->client->telephone=telephone;
            i=i+1;
        }
    }
    if(i==-1)
    {
        printf(" \n le client n'existe pas pour modifier      !! " );

    }
}
ClientElement*  getclient(ClientElement  *list_client)
{
    FILE *fichier=NULL;
    client* nouv;
    int code;
    char text_nom[50];
    char text_prenom[50];
    char text_telephone[50];

    char* nom;
    char* prenom;
    char* telephone;

    fichier = fopen("bd_client.txt","r");
      if (fichier != NULL)
    {
        while(!feof(fichier))
        {
            fscanf(fichier,"%d %s %s %s\n",&code,&text_nom,&text_prenom,&text_telephone);
            nom=(char*)malloc(sizeof(char)*strlen(text_nom));
            strcpy(nom,text_nom);
            prenom=(char*)malloc(sizeof(char)*strlen(text_prenom));
            strcpy(prenom,text_prenom);
            telephone=(char*)malloc(sizeof(char)*strlen(text_telephone));
            strcpy(telephone,text_telephone);
            nouv=createClient(code,nom,prenom,telephone);
            list_client=ajouterClientElement(list_client,nouv);
        }
        return list_client;
        // On peut lire et écrire dans le fichier
    }
    else
    {

        return NULL;
    }
    fclose(fichier);
}
void bd_client(ClientElement* list_Client)
{
    FILE *fichier=NULL;

    ClientElement* tmp;
    fichier = fopen("bd_client.txt", "w");
      if (fichier != NULL)
    {
        for(tmp=list_Client;tmp!=NULL;tmp=tmp->nxt)
        {
            fprintf(fichier,"%d %s %s %s\n",tmp->client->code
                    ,tmp->client->nom,tmp->client->prenom,tmp->client->telephone);
        }

    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
        return ;
    }
    fclose(fichier);
}
void mainClient()
{
    printf("heello");
    ClientElement* listClient=NULL;
    listClient=getclient(listClient);
    int choix;
    int code;
    client* client;
    do
    {
        printf("\n ******************     Le menu  ************************   \n");
        printf(" ***    1 : Ajouter un client dans la liste des clients  \n ");
        printf(" ***    2 : afficher La liste des clients   \n ");
        printf(" ***    3 : supprimer un client  \n ");
        printf(" ***    4 : Recherche un client  \n ");
        printf(" ***    5 : modifier un client  \n ");
        printf(" ***    6 : Menu Principale  \n ");
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
                listClient=ajouterClient(listClient);break;
            case 2:
                system("cls");
                if(test_liste_client(listClient))
                {
                   display_liste_client(listClient);
                }
                else printf("la liste des client est vide");
                break;
            case 3:
                system("cls");

               printf(" ***   \n  entrez le code du client que vous voullez Supprimer  :  ");
               scanf("%d",&code);

                 listClient=supprimerClient(listClient,code); break;
            case 4:
               system("cls");
               printf(" ***   \n  entrez le code du client que vous voullez Rechercher  :  ");
               scanf("%d",&code);
               client=RechercherClient(listClient,code);
                if(client!=NULL)
                {
                    printf(" !!!    voila le client    :  \n ");
                displayClient(client);
                }
                else
                    printf("votre client n'existe pas dans cette base de donnée \n !!!! ");

                    break;


            case 5 :
               system("cls");
               printf(" ***   \n  entrez le code du client que vous voullez Modifier  :  ");
               scanf("%d",&code);

                ModifierClient(listClient,code); break;
            case 6:

                system("cls");
                mainPrincipale();
                break;


        }



    }while(choix!=7);
   bd_client(listClient);

}
