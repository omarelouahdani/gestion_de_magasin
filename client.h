#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

typedef struct client client;
struct client
{
    int code;
    char *nom;
    char *prenom;

    char* telephone;

};

typedef struct ClientElement ClientElement;
struct ClientElement
{
    client *client;
    ClientElement *nxt;
};
client* createClient (int code ,char* nom ,char *prenom ,char *telephone);

ClientElement *CreatClientElement(client *client);

ClientElement* ajouterClientElement(ClientElement*  listClient , client* client);

void displayClient(client *client);
void display_liste_client(ClientElement* listClient);
int test_liste_client(ClientElement *listClient);
char* saisietxt();
ClientElement* ajouter(ClientElement* listClient);
ClientElement* supprimerClient(ClientElement* listClient,int code);
client* RechercherClient(ClientElement* listClient , int code);
ClientElement* ModifierClient(listClient,code);
ClientElement*  getclient(ClientElement  *list_client);
void bd_client(ClientElement* list_Client);
void  mainClient();
#endif // CLIENT_H_INCLUDED
