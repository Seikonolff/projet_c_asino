
#include "slots.h"
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()
#include <stdio.h> // pour printf et scanf
#include <string.h> // pour strcpy
#define initial_stack 1000
#define nombre_item 4
#define nombre_rouleaux 3



slot rouleaux[nombre_rouleaux]; //définition d'un tableau rouleaux de 3 structures slot

void init_rouleaux()
{
strcpy(rouleaux[0].nom_slot,"Rouleau 0");
strcpy(rouleaux[1].nom_slot, "Rouleau 1");
strcpy(rouleaux[2].nom_slot, "Rouleau 2");
}

char* item0; //définition de l'item du rouleau X

//int stack = player.credits;
int stack = initial_stack;
int playerbet;
int gain;

int tirage_slot()
{
    srand(time(NULL)); //redemarrage du timer pour plus d'aléatoire
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
    if (rouleaux[0].item == rouleaux[1].item || rouleaux[1].item == rouleaux[2].item || rouleaux[2].item == rouleaux[0].item)
    {
        gain = playerbet;
        return gain;
    }
    if (rouleaux[0].item != rouleaux[1].item && rouleaux[1].item != rouleaux[2].item && rouleaux[2].item != rouleaux[0].item)
    {
        gain = -playerbet;
        return gain;
    }
    return 0; //no gair nor loss
}

void slots_game()
{
    printf("Début du jeu de la machine à sous ! \n Vous avez %d $ \n", stack);
    printf("Combien voulez vous misez ?\n");
    scanf("%d", &playerbet);
    init_rouleaux();
    for (int i = 1; i< nombre_rouleaux; i++)
    {
        rouleaux[i].item = tirage_slot();
    }
    printf("%-20s |%-20s |%-20s |\n",affichage_item(0), affichage_item(1), affichage_item(2));
    check_results();
    stack += gain;
    printf("Votre nouveau stack est %d \n", stack);
}