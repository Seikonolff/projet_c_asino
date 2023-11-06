
#include "slots.h"
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()
#include <stdio.h> // pour printf et scanf
#include <string.h> // pour strcpy
#include <unistd.h> //pour usleep (en microsecondes)
#define initial_stack 1000
#define nombre_item 4
#define nombre_rouleaux 3
#define true 1

slot rouleaux[nombre_rouleaux]; //définition d'un tableau rouleaux de 3 structures slot

char* item0; //définition de l'item du rouleau X
int stack = initial_stack;
int playerbet;
int profit;

void init_rouleaux()
{
strcpy(rouleaux[0].nom_slot,"Rouleau 0");
strcpy(rouleaux[1].nom_slot, "Rouleau 1");
strcpy(rouleaux[2].nom_slot, "Rouleau 2");
}

void init_aleatoire()
{
    srand(time(NULL));
}

int tirage_slot()
{
    //srand(time(NULL)); //redemarrage du timer pour plus d'aléatoire
    //rouleaux[rouleau].item = rand()%4;
    //return rouleaux[rouleau].item;
    return rand()%nombre_item;
}

char* affichage_item(int rouleau)
{
    switch(rouleaux[rouleau].item)
        {
            case 0: {item0="BELL";return item0;}
            case 1: {item0="BAR";return item0;}
            case 2: {item0="CHERRIES";return item0;}
            default: {item0="7";return item0;}
        }
}

int check_results() 
{
    if (rouleaux[0].item == rouleaux[1].item && rouleaux[1].item == rouleaux[2].item)
        {return 2;}

    if (rouleaux[0].item == rouleaux[1].item || rouleaux[1].item == rouleaux[2].item || rouleaux[2].item == rouleaux[0].item)
    {return 1;}

    if (rouleaux[0].item != rouleaux[1].item && rouleaux[1].item != rouleaux[2].item && rouleaux[2].item != rouleaux[0].item)
    {return 0;}
    return 0; //no gair nor loss
}

int gain(int mise, int resultat){
    switch (resultat)
    {
    case 0 : return 0; break;
    case 1 : return 1.5*mise; break;
    case 2 : return 10*mise; break;
    default: break;
    }
}

void slots_game()
{
    char reponse[10];
    printf("Début du jeu de la machine à sous ! \n Vous avez %d $ \n", stack);
    //printf("Tapez 0 pour retourner au lobby, 1 pour jouer à la machine à sous.\n");
    while (true){
    printf("Combien voulez vous misez ?\n");
    scanf("%d", &playerbet);
    while (playerbet > stack){
        printf("Pas assez d'argent pour miser %d $, votre mise max est de %d $ \n", playerbet, stack);
        printf("Combien voulez vous misez ?\n");
        scanf("%d", &playerbet);
    }
    printf("Votre mise est de %d $ \n", playerbet);
    stack -= playerbet;
    init_rouleaux();
    init_aleatoire();

    for (int j=0; j<5; j++){
    for (int i = 0; i< nombre_rouleaux; i++)
    {
        rouleaux[i].item = tirage_slot();
    }
    printf("%-20s |%-20s |%-20s |\n",affichage_item(0), affichage_item(1), affichage_item(2));
    sleep(0.1);
    }

    profit = gain(playerbet, check_results());
    stack += profit;
    if (check_results()==2){
        printf("JACKPOT!!!!!\n");
    }
    if (profit !=0){
        printf("Bravo ! Vous avez gagné %d $ \n", profit);
    }
    else{
        printf("GAME OVER\n");
        printf("T'as perdu sale chien hahaha \n");
    }
    printf("Votre nouveau stack est %d $ \n", stack);
    printf("Voulez vous continuer à jouer ? (o/n)\n");
    scanf("%s",reponse);

    if(reponse[0]=='o'||reponse[0]=='O')//on regarde le premier cara de la chaine
		{
		if(stack==0){
            printf("T'as plus d'argent, tu peux plus jouer!!\n");
            break;
            }
        }//on continue dans la boucle de jeu
    else {break;}
    /*
    if(reponse[0]=='n' || reponse[0]=='N'){
        break;
    }
    else 
		{
        printf("Nous n'avons pas compris, merci de répondre par oui ou non \n");
		}
    */
    } 
}  