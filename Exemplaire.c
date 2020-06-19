#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Livre.h"
#include "usefulFunctions.h"
typedef struct SExemplaire{
	int IdExempl;
	int IdLivre;
	int dispo;
	struct SExemplaire *next;
}Exempl;

int is_empty1(Exempl *C) //Verifier si la liste est vide
{
	if(C == NULL) 
		return 1;
	return 0;
	
}

int FileEmpty1(FILE *file) // Verifier si le ficher Exemplaire est vide
{ 
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0){
        return 1;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 0;
}

void AddExemplaire() // Ajouter un exemplaire
{
	int idLivre;
	FILE *f = fopen("Exemplaire.txt", "a+");
	Exempl *New;
	do{
	printf("donner le id livre :");
	scanf("%d",&idLivre);
	  if(livre_exsite(idLivre) == 0)
	printf("ce id livre n'existe pas \n");
	}while(livre_exsite(idLivre) == 0);
	New = malloc(sizeof(Exempl));
	New->IdExempl = getId("Exemplaire.txt") + 1;
	New->IdLivre = idLivre;
	New->dispo = 1;
	New -> next = NULL;
	
	if(FileEmpty1(f) == 1)
	{
		fprintf(f,"%d:%d:%d", New -> IdExempl, New -> IdLivre, New -> dispo);
		printf("l\'exemplaire est bien ajoute");
		fclose(f);
		return;
	}
	else
	{
		fprintf(f,"\n%d:%d:%d", New -> IdExempl, New -> IdLivre, New -> dispo);
		printf("l\'exemplaire est bien ajoute");
		fclose(f);
		return;
	}		
	
}

Exempl * AddExemplaireToList(Exempl* List, int idE, int idL, int dispo) // Ajouter un Client a la list chainee
{
	Exempl * E = malloc(sizeof(Exempl));
	E -> IdExempl = idE;
	E -> IdLivre = idL;
	E -> dispo = dispo;
	E -> next = NULL;
	
	if(is_empty1(List) == 1){
		List = E;
		return List;
	}
	else{
		Exempl *pt;
		Exempl *pos;
		
		pt = List;
		while(pt->next != NULL)
		{
			pos = pt;
			pt = pt -> next;
		}
		pt -> next = E;
		return List;
	}
}

Exempl * getExempls(char* File) // Generer une liste chainee dapres le ficher Exemaplaire.txt
{
	unsigned int idE, idL, dispo;
	Exempl *ListExempl=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		idE = atoi(SaisirChaine(f));
		idL = atoi(SaisirChaine(f));
		dispo = atoi(SaisirChaine(f));
		ListExempl = AddExemplaireToList(ListExempl, idE, idL, dispo);
	}
	fclose(f);
	return ListExempl;
}

void AfficherTousLesExemplaires() // Afficher Tous les Exemplaire
{
	printf("\nL\'affichage de tous les exempaires\n");
	Exempl *AllExempl = getExempls("Exemplaire.txt");
	Exempl *E;
	E = AllExempl;
	if(E == NULL){
		printf("Il n\'y a pas des Exemplaires");
		return;
	}
	else{
		while(E != NULL)
		{
			printf("--------------------------------------");
			printf("\nIdExemplaire:\t%i\n", E->IdExempl);
			printf("\nIdLivre:\t%i\n", E->IdLivre);
			printf("\ndisponible:\t%i\n", E->dispo);
		;
			E = E -> next;
		}
	}
	
}

void RefrechExemplaires(Exempl* list,char * file) // mis a jour le ficher Exemplaire
{
	if(list == NULL)
	{
		printf("la list est vide");
		return;
	}
	FILE * f = fopen(file , "w");
	if(f == NULL)
	{
		printf("Can\'t open the file");
		return;
	}
	Exempl *curent;
	curent = list;
	while(curent != NULL){
		fprintf(f, "%d:", curent->IdExempl);
		fprintf(f, "%d:", curent->IdLivre);
		if(curent -> next != NULL)
		{
			fprintf(f, "%d\n",  curent -> dispo);
		}
		else if (curent -> next == NULL)
		{
			fprintf(f, "%d",  curent -> dispo);
	}
		curent = curent -> next;
	}
	fclose(f);
}

void changerInfoExemplaires(int id) // modifier les info un exemplaire dapres son ID
{
	Exempl *AllExempl = getExempls("Exemplaire.txt");
	int choix;
	int info;
	char *word;
	Exempl *E;
	E = AllExempl;
		if(E == NULL){
		printf("Il n\'y a pas des exemplaires");
		return  ;
	}
	else{
		while(E != NULL)
		{
			if(E->IdExempl == id)
			{
				printf("\nChoisissez ce que vous voulez changer:\n1 - Id Livre\n2 - Disponible\n");
				scanf("%i", &choix);
				getchar();
				switch(choix)
				{
					case 1 :
						do{
						printf("Inserer le nouveau ID Livre: ");
						scanf("%d", &info);
					}while(info < 0 );
						E -> IdLivre = info;
						break;
					case 2 :
						do{
						printf("Inserer si l\'exemplaire est disponible 1 si oui et 0 sinon: ");
						scanf("%d", &info);
						printf("\ninfo = %d\n", info);
					}while(info != 0 && info != 1);
					//	word = strtok(info, "\n");
						E -> dispo = info;
						break;
				}
				printf("\nLe nouveau profil d\'exemplaire est : \n");
				printf("\nId Exemplaire:\t%i\n", E->IdExempl);
				printf("\nId Livre:\t%i\n", E->IdLivre);
				printf("\nDisponible:\t%i\n", E->dispo);
				do{
					printf("voulez vous sauvgarder les changements ? \n");
					printf("entez 1 pour valider ou 0 sinon : ");
					scanf("%d",&choix);
				    }while((choix != 0) && (choix != 1));
					if(choix == 1){
				    	RefrechExemplaires(AllExempl,"Exemplaire.txt");
				    	printf("vous avez sauvgarder.\n");
				    	return ;
				    }
				    else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				     }
			}
			E = E -> next;
		}
		printf("Cette Exemplaire n\'existe pas");	
		return;
	}
	
}

void deleteExemplaire(int id) // Supprimer un Exemplaire dapres son ID
{
	int choix;
	Exempl *AllExempls = getExempls("Exemplaire.txt");
	Exempl *CExempl; // Curent Exemplaire
	Exempl *PExempl = NULL; // Previous Exemplaire
	
	if(AllExempls == NULL){
	printf("Il n\'y a pas des exemplaires");
	return  ;
	}
	else{
		for(CExempl = AllExempls; CExempl != NULL; PExempl = CExempl, CExempl = CExempl -> next)
		{
			if(CExempl->IdExempl  == id)
			{
				if(PExempl == NULL)
				{
					AllExempls = CExempl -> next;
				do{
					printf("voulez vous sauvgarder les changements ? \n");
					printf("entez 1 pour valider ou 0 sinon : ");
					scanf("%d",&choix);
				    }while((choix != 0) && (choix != 1));
					if(choix == 1){
				    	RefrechExemplaires(AllExempls,"Exemplaire.txt");
				    	printf("vous avez sauvgarder.\n");
				    	return ;
				    }
				    else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				     }
				         
				}
				else
				{
					if(CExempl -> next == NULL)
					{
						PExempl -> next = NULL;
				do{
					printf("voulez vous sauvgarder les changements ? \n");
					printf("entez 1 pour valider ou 0 sinon : ");
					scanf("%d",&choix);
				    }while((choix != 0) && (choix != 1));
					if(choix == 1){
				    	RefrechExemplaires(AllExempls,"Exemplaire.txt");
				    	printf("vous avez sauvgarder.\n");
				    	return ;
				    }
				    else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				     }
					}
					else
					{
						PExempl -> next = CExempl -> next;
				do{
					printf("voulez vous sauvgarder les changements ? \n");
					printf("entez 1 pour valider ou 0 sinon : ");
					scanf("%d",&choix);
				    }while((choix != 0) && (choix != 1));
					if(choix == 1){
				    	RefrechExemplaires(AllExempls,"Exemplaire.txt");
				    	printf("vous avez sauvgarder.\n");
				    	return ;
				    }
				    else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				     }
					}
				}
			}
		}
	}
	printf("l\'exemplaire n\'existe pas");
	return ;
}

void ChercherExemplaire()
{
	Exempl *All;
	Exempl *E;
	int id, disp = 2, choix = 0;
	char temp;
	
	All = getExempls("Exemplaire.txt");
	E = All;
	if(E == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}
	
	printf("\nRecherche par id exemplaire : 1\n");
	printf("Recherche par id livre : 2\n");
	printf("Recherche par disponibilite : 3\n");
	do{
	printf("Votre choix :");
	scanf("%d",&choix);
	}while(choix != 1 && choix != 2 && choix != 3);
	switch(choix){
		
		case 1:
			printf("\nDonner id de l\'exemplaire que vous cherchez :");
			scanf("%d",&id);
			while(E != NULL)
			{
				if(E->IdExempl == id)
				{
					printf("\n--------------------------------\n");
					printf("\nId Exemplaire:\t%i\n", E->IdExempl);
					printf("\nId Livre:\t%i\n", E->IdLivre);
					printf("\nDisponible:\t%i\n", E->dispo);
					printf("--------------------------------\n");
					return;
				}
				E = E->next; 
			}
			printf("\nCette id n\'existe pas\n");
			return;
		case 2:
			printf("\nDonner id de livre que vous cherchez :");
			scanf("%d",&id);
			while(E != NULL)
			{
				if(E->IdLivre == id)
				{
					printf("\n--------------------------------\n");
					printf("\nId Exemplaire:\t%i\n", E->IdExempl);
					printf("\nId Livre:\t%i\n", E->IdLivre);
					printf("\nDisponible:\t%i\n", E->dispo);
					printf("--------------------------------\n");
					
				}
				E = E->next;
			}
			printf("\nRecherche termine\n");
			return;
		case 3:
			do{
			printf("\nDonner la disponibilite que vous cherchez (1: disponible | 0: Nom disponible) :");
			scanf("%d",&disp);
			}while(disp != 0 && disp != 1);
			if(disp == 0)
			{
				while(E != NULL)
				{
					if(E->dispo == 0)
					{
						printf("\n--------------------------------\n");
						printf("\nId Exemplaire:\t%i\n", E->IdExempl);
						printf("\nId Livre:\t%i\n", E->IdLivre);
						printf("\nDisponible:\t%i\n", E->dispo);
						printf("--------------------------------\n");	
					}
					E = E->next;
				}
			}
			else if(disp == 1)
			{
				while(E != NULL)
				{
					if(E->dispo == 1)
					{
						printf("\n--------------------------------\n");
						printf("\nId Exemplaire:\t%i\n", E->IdExempl);
						printf("\nId Livre:\t%i\n", E->IdLivre);
						printf("\nDisponible:\t%i\n", E->dispo);
						printf("--------------------------------\n");	
					}
					E = E->next;
				}
			}
			printf("\nRecherche termine\n");
			return;
		
	}
}


void changer_dispo(int id, int dispo)
{
	Exempl *All;
	Exempl *E;
	
	All = getExempls("Exemplaire.txt");
	E = All;
	if(E == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}
	while(E != NULL)
	{
		if(E->IdExempl == id)
		{
			E->dispo = dispo;
			printf("\nChangement effectue.\n");
			return;
		}
		E = E->next;
	}
	printf("\nCette id n\'existe pas\n");
	return;
	
}




