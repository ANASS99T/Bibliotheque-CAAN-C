#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Categorie.h"
#include"Auteur.h"
#include "usefulFunctions.h"

typedef struct Livre{
	int idlivre;
	char *titreLivre;
    int idAuteur;
    int idCategorie;
	struct Livre *suivant; 
}Livre;

Livre *AjouterLivreliste(Livre *liste ,int idlivre,char *titre, int idAuteur, int idCategorie)
{
	Livre *nouveau = (Livre*)malloc(sizeof(Livre));
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return NULL;
	}
	nouveau->idlivre = idlivre;
	nouveau->titreLivre = titre;
	nouveau->idAuteur  = idAuteur;
	nouveau->idCategorie = idCategorie;
	nouveau->suivant=NULL;
	Livre *courant = liste;
	if(liste == NULL)
	{
		liste = nouveau;
	}
	else {
	while(courant->suivant!=NULL)
	{
		courant = courant->suivant;
		
	}
	courant->suivant=nouveau;
    }
    return liste;
}


Livre *Chargerlivre(char *fich)
{   FILE * f = fopen(fich, "r") ;
    Livre *liste = NULL;
	int idlivre;
	char *titre;
	int idAuteur;
	int idCategorie;
	int i = 0;
    if(f==NULL){
		printf("erreur d'ouvrire le file '");
		return NULL;
	}
	if(fgetc(f)==EOF){	
	return NULL;
	}
	else{
	fseek(f,0,SEEK_SET);
    }
	while(!feof(f))
	{
		idlivre = atoi(SaisirChaine(f));
		titre = SaisirChaine(f);
		idAuteur = atoi(SaisirChaine(f));
		idCategorie = atoi(SaisirChaine(f));
       liste = AjouterLivreliste(liste,idlivre,titre,idAuteur,idCategorie);
	}
	fclose(f);
	return liste;
}
void insererlivre(Livre *liste , char *fich)
{   FILE * f = fopen(fich, "w") ;
	Livre *courant;	
	courant = liste;
	while(courant!=NULL){
		fprintf(f,"%d:",courant->idlivre);
		fprintf(f,"%s:",courant->titreLivre) ;
		fprintf(f,"%d:",courant->idAuteur);
		if(courant->suivant!=NULL)
			fprintf(f,"%d\n", courant->idCategorie) ;
		else if (courant->suivant==NULL)
			fprintf(f,"%d", courant->idCategorie) ;
		courant=courant->suivant;		
	}
	fclose(f) ;	
}


void afficherlivre(char *fich)
{
	Livre *liste = NULL;
	liste = Chargerlivre(fich);
	Livre *courant =liste;
	printf("--------------------Touts les livres de la bibliotheque ---------------------");
	while(courant != NULL){
	printf("\n---------------------------------------------------------\n");
	printf("Id du livre \t\t\t:%d\t\t\n",courant->idlivre);
	printf("Nom du livre \t\t\t:%s\t\t\n",courant->titreLivre);
    printf("Auteur du livre \t\t:%d\t\t\n",courant->idAuteur);
    printf("Categorie du livre \t\t:%d\t\t\n",courant->idCategorie);
	courant = courant->suivant;
 }
}


void modifierlivre()
{
	int idlivre;
	int choix;
	int choix2;
	Livre *liste,*courant;
	liste = Chargerlivre("Livres.txt");
	if(liste == NULL){
		printf("le fichier  est vide \n");
		return ;
	}
	else{
	printf("donner ancien id du livre que vous souhaitez modifier : ");
	scanf("%d",&idlivre);
	getchar();
	courant = liste; 
	while ((courant!=NULL) && (courant->idlivre != idlivre)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet  id n existe pas dans le fichier !\n");
		return;
	}
	else if(courant->idlivre == idlivre) {
	printf("Modifier le nom du livre : 1\n");
	printf("Modifier auteur du livre : 2\n");
	printf("Modifier la categorie du livre : 3\n");
	printf("Votre choix :");
	scanf("%d",&choix2);
	getchar();
	if(choix2 == 1)
	{
        printf("Donner le nouveau titre du livre:");
		courant->titreLivre = SaisirChaine(stdin);
	}
	else if(choix2 == 2)
	{
        printf("Donner le nouveau Id auteur du livre:");
        scanf("%d",&courant->idAuteur);
        getchar();
	}
	else if(choix2 == 3)
	{
        printf("Donner le nouveau id categorie du livre:");
        scanf("%d",&courant->idCategorie);
        getchar();
	}
  
	}
	do{
	printf("voulez vous vraiment modifier le livre ? \n");
	printf("entrez 1 pour valider / 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	insererlivre(liste,"Livres.txt");
    	printf("\nModification effectue  avec succes !\n");
    }
    else if (choix == 0)
         printf("\nModification abandonne\n");
}
}


void AjouterLivrelistefich()
{
	Livre *liste,*courant ;
	int idlivre,choix;
	char *titre;
	int idAuteur;
	int idCategorie;
	int i ;
	liste = Chargerlivre("Livres.txt");
	courant = liste;
	while(courant->suivant!=NULL){
		courant = courant->suivant;
	}
	i=courant->idlivre;
	printf("ATTENTION! id du livre commence a partir de %3d\n",i+1);
	printf("\nid du livre :");
	scanf("%d",&idlivre);
	getchar();
	printf("titre du livre :");
	titre = SaisirChaine(stdin);
	do{
	printf("idAuteur :");
    scanf("%d",&idAuteur);
    if(existeAuteur(idAuteur) == 0)
       printf("y'a pas un auteur avec ce id \n");
    }while(existeAuteur(idAuteur) == 0);
    
    do{
    printf("Categorie du livre:");
    scanf("%d",&idCategorie);
    if(existeCategorie(idCategorie) == 0)
       printf("y'a pas une categorie avec ce id \n");
    }while(existeCategorie(idCategorie) == 0);
    

	if(liste == NULL){
		liste = AjouterLivreliste(liste,idlivre,titre,idAuteur,idCategorie);
	}
	else{
	Livre *nouveau = (Livre*)malloc(sizeof(Livre));
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return;
	}
	nouveau->idlivre = idlivre;
	nouveau->titreLivre = titre;
	nouveau->idAuteur = idAuteur;
	nouveau->idCategorie = idCategorie;
	nouveau->suivant=NULL;
	courant = liste;
	while((courant->suivant!=NULL) && (courant->idlivre != idlivre)){
		courant = courant->suivant;
	}
	if(courant->idlivre == idlivre){
		printf("\nCet id existe deja  !\n");
		return;
	}
	else if ((strcmp(titre,courant->titreLivre) == 0) && (idAuteur == courant->idAuteur) && (idCategorie == courant->idCategorie)){
	 	printf("\nIl existe deja un livre avec les memes informations!\n");
	 	return;
	 }
	else if(courant->suivant == NULL){
		 courant->suivant=nouveau;
	}
    }
	do{
	printf("\nConfirmer ajout :\n");
	printf("\nentrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    insererlivre(liste ,"Livres.txt");	
    	printf("\najout effectuez avec succes\n");
    }
    else if (choix == 0)
         printf("\nAjout abandonne\n");
}
void supprimerlivre()
{
	int idlivre;
	int choix;
	Livre *liste;
	Livre *courant,*precourant;
	liste = Chargerlivre("Livres.txt");
	if(liste == NULL){
		printf("\nAucun livre dans le fichier! \n");
		return ;
	}
	else{
	printf("donner id du livre a supprimer : ");
	scanf("%d",&idlivre);
	getchar();
	if (liste->idlivre == idlivre){
	precourant=liste;
	liste =liste->suivant;
	free(precourant);
    }
    else{
    	courant = liste;
    	while((courant != NULL) && (courant->idlivre != idlivre))
	    {
	    	precourant = courant;
	    	courant =courant->suivant;
	    }
	    if(courant == NULL){
	    	printf("\nAucun livre ne possede ce id :");
	    	return;
		}
	   
	   	precourant->suivant=courant->suivant;
	   	free(courant);
	   }
	}
	do{
	printf("\nvoulez vous sauvgarder les changements ? \n");
	printf("entrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	insererlivre(liste ,"Livres.txt");
    	printf("\nlivre supprimer avec succes !\n");
    }
    else if (choix == 0)
         printf("\nsuppression abandonne!\n");
}


void rechercherlivre()
{
	Livre *liste;
	int idlivre,choix;
	char *titre;
    int idAuteur;
	int idCategorie;
	liste = Chargerlivre("Livres.txt");
	if(liste == NULL){
		printf("\nle fichier  est vide \n");
		return ;
	}
	else{
	Livre *courant,*courant2;
	printf("Recherche par id : 1\n");
	printf("Recherche par nom du livre : 2\n");
	printf("Recherche par Id d'auteur du livre : 3\n");
	printf("Recherche par id categorie du livre : 4\n");
	printf("Votre choix :");
	scanf("%d",&choix);
	getchar();
	if(choix == 1){
		courant = liste;
		printf("Donner id du livre que vous cherchez :");
		scanf("%d",&idlivre);
		
	 while ((courant!=NULL) && (courant->idlivre != idlivre)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet  id nexiste pas dans le fichier !\n");
		return;
	}
	else{
	printf("\n---------------------------------------------------------\n");
	printf("Id du livre \t\t\t: %d\t\t\n",courant->idlivre);
	printf("Nom du livre \t\t\t: %s\t\t\n",courant->titreLivre);
    printf("Auteur du livre \t\t: %d\t\t\n",courant->idAuteur);
    printf("Categorie du livre \t\t: %d\t\t\n",courant->idCategorie);
	}
	}
	else if(choix == 2)
	{   courant = liste;
        printf("Donner le titre du ou des livres que vous cherchez:");
		titre = SaisirChaine(stdin);
	   while ((courant!=NULL) && (strcmp(titre,courant->titreLivre ) != 0)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet nom  nexiste pas dans le fichier !\n");
		return;
	}
	else {
	while(courant!=NULL)
	{
	if(strcmp(titre,courant->titreLivre ) == 0)
	{
	printf("\n------------Tous les livres de ce nom----------------------------\n");
	printf("Id du livre \t\t\t: %d\t\t\n",courant->idlivre);
	printf("Nom du livre \t\t\t: %s\t\t\n",courant->titreLivre);
    printf("id Auteur du livre \t\t: %d\t\t\n",courant->idAuteur);
    printf("id Categorie du livre \t\t: %d\t\t\n",courant->idCategorie);
	}
	 courant = courant->suivant;
	}
     }
    }
		else if(choix == 3)
	{   courant = liste;
        printf("Donner le id de lauteur que vous cherchez:");
		scanf("%d",idAuteur);
		getchar();
	  while ((courant!=NULL) && (idAuteur != courant->idAuteur)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet auteur nexiste pas dans le fichier !\n");
		return;
	}
	else {
	while(courant!=NULL)
	{
	if(idAuteur == courant->idAuteur)
	{
	printf("\n---------Tous les livres de cet auteur-----------------------\n");
	printf("Id du livre \t\t\t: %d\t\t\n",courant->idlivre);
	printf("Nom du livre \t\t\t: %s\t\t\n",courant->titreLivre);
    printf("id Auteur du livre \t\t: %d\t\t\n",courant->idAuteur);
    printf("id Categorie du livre \t\t: %d\t\t\n",courant->idCategorie);
	}
	 courant = courant->suivant;
	}
    }
	}
	else if(choix == 4)
	{   courant = liste;
        printf("Donner le id categorie du ou des livres que vous cherchez:");
		scanf("%d",idAuteur);
		getchar();
	    while ((courant!=NULL) && (idCategorie != courant->idCategorie)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cette categorie  nexiste pas dans le fichier !\n");
		return;
	}
	else {
	while(courant!=NULL)
	{
	if(idCategorie != courant->idCategorie)
	{
	printf("\n---------------------------------------------------------\n");
	printf("Id du livre \t\t\t: %d\t\t\n",courant->idlivre);
	printf("Nom du livre \t\t\t: %s\t\t\n",courant->titreLivre);
    printf("id Auteur du livre \t\t: %d\t\t\n",courant->idAuteur);
    printf("id Categorie du livre \t\t: %d\t\t\n",courant->idCategorie);
	}
	 courant = courant->suivant;
	}
    }
	}
}	
}

int livre_exsite(int idLivre){
	Livre *liste,*courant;
	liste = Chargerlivre("Livres.txt");
	courant=liste;
	while(courant != NULL){
		if(courant->idlivre == idLivre)
			return 1; 
		courant = courant->suivant;
	}	
return 0;
}





