
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
//float stack = initial_stack;


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
            case 3: {item0="7";return item0;}
            default: {item0="ERREUR";return item0;}
        }
}

int check_results() 
{
    for (int j=0; j<3; j++){
        if (affichage_item(j) == "ERREUR") //strcmp renvoie 0 si les deux chaines sont identiques
            {return 0;}
        }
    if (rouleaux[0].item == rouleaux[1].item && rouleaux[1].item == rouleaux[2].item)
    {return 3;}

    if (rouleaux[0].item == rouleaux[1].item || rouleaux[1].item == rouleaux[2].item || rouleaux[2].item == rouleaux[0].item)
    {return 2;}

    if (rouleaux[0].item != rouleaux[1].item && rouleaux[1].item != rouleaux[2].item && rouleaux[2].item != rouleaux[0].item)
    {return 1;}
    return 0; //no gair nor loss
}

float gain(float mise, int resultat){
    switch (resultat)
    {
    case 0 : return mise; break; //cas d'une erreur lors du tirage
    case 1 : return 0; break;    //défaire du joueur
    case 2 : return 1.5*mise; break; //half house soit 2 item identiques
    case 3 : return 10*mise; break; //trois items identiques
    default: return mise; break;   //par défaut, erreur machine donc le joueur perd rien
    }
}

float slots_game(float stack)
{
    char reponse[10];
    float playerbet;
    int playerbet_int;
    float profit;
    printf("Début du jeu de la machine à sous ! \n Vous avez %f $ \n", stack);
    //printf("Tapez 0 pour retourner au lobby, 1 pour jouer à la machine à sous.\n");

    while (true){
        printf("Combien voulez vous miser ?\n");
        scanf("%f", &playerbet);
        while (playerbet > stack){
            printf("Pas assez d'argent pour miser %f $, votre mise max est de %f $ \n", playerbet, stack);
            printf("Combien voulez vous miser ?\n");
            scanf("%f", &playerbet);
        }
        while (playerbet < 10){
            printf("La mise minimale est de 10$.\n");
            printf("Combien voulez vous miser ?\n");
            scanf("%f", &playerbet);
        }
        playerbet_int = (int)playerbet;
        while (playerbet != playerbet_int){
            printf("Le jeton le plus petit est 1$, vous ne pouvez pas miser des centimes.\nCombien voulez vous miser ?\n");
            scanf("%f", playerbet);
        }
        printf("Votre mise est de %f $ \n", playerbet);
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
        switch (check_results())
        {
        case 0 : printf("Desole, erreur dans le tirage, vous n'avez rien perdu.\n");break;
        case 1 : printf("Vous avez perdu...\n");break;
        case 2 : printf("Bravo ! Vous avez gagné %f $ \n", profit);break;
        case 3 : printf("JACKPOT!!!!!\nVous avez gagné %f $\n", profit);break;
        default: break;
        }
        printf("Votre nouveau stack est %f $ \n", stack);
        printf("Voulez vous continuer à jouer ? (o/n)\n");
        scanf("%s",reponse);

        if(reponse[0]=='o'||reponse[0]=='O')//on regarde le premier cara de la chaine
            {
            if(stack<10){
                printf("Retournez a la banque pour deposer des $$$!!\n");
                return stack; break;
                }
            }
        else { return stack; break;} //on continue dans la boucle de jeu
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