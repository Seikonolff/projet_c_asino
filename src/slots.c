
#include "slots.h"
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()
#include <stdio.h> // pour printf et scanf
#include <string.h> // pour strcpy
#include <unistd.h> //pour usleep (en microsecondes)
#include <math.h> //pour floor (arrondir a l'entier inférieur)

#define nombre_item 4
#define nombre_rouleaux 3
#define mise_mini 10
#define true 1
#define false 0

slot rouleaux[nombre_rouleaux]; //définition d'un tableau rouleaux de 3 structures slot

char* item0; //définition de l'item du rouleau X

void clear_terminal(){
    for (int i=0; i<80; i++)
    {printf("\n");}
}
void affichage_stack(float stack_a_afficher){
    printf("%95.s", " ");
    printf("+--------------------+\n");
    printf("%95.s", " ");
    printf("|STACK: %10.2f $ |\n",stack_a_afficher);
    printf("%95.s", " ");
    printf("+--------------------+\n");
    printf("\n \n");
}

float mise_joueur(){
    float mise;
    printf("Combien voulez vous miser ?\n");
    scanf("%f", &mise);
    return mise;
}

float mise_conforme(float bet_joueur, float stack_joueur){
    int playerbet_int;
    playerbet_int = (int)bet_joueur;
    if (bet_joueur <= stack_joueur){
        if (bet_joueur >= mise_mini){
            if (bet_joueur != playerbet_int){
                clear_terminal();
                affichage_stack(stack_joueur);
                printf("Le jeton le plus petit est 1$, vous ne pouvez pas miser des centimes.\n");
                return 3;
            }
            else {
                return 0;}
        }
        else {
            clear_terminal();
            affichage_stack(stack_joueur);
            printf("La mise minimale est de 10$.\n");
            return 2;
            }
    }
    else {
        clear_terminal();
        affichage_stack(stack_joueur);
        printf("Pas assez d'argent pour miser %.2f $, votre mise max est de %.0f $ \n", bet_joueur, floor(stack_joueur));
        return 1;
        }
}

float cas_conformite(int cas_conforme, float bet_joueur_2, float stack_joueur2){
    while (cas_conforme != 0){
        bet_joueur_2 = mise_joueur();
        cas_conforme = mise_conforme(bet_joueur_2, stack_joueur2);
    }
    return bet_joueur_2;
    
}

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
    {return 3;} //jackpot, 3 items identiques

    if (rouleaux[0].item == rouleaux[1].item || rouleaux[1].item == rouleaux[2].item || rouleaux[2].item == rouleaux[0].item)
    {return 2;} // 2 items identiques 

    if (rouleaux[0].item != rouleaux[1].item && rouleaux[1].item != rouleaux[2].item && rouleaux[2].item != rouleaux[0].item)
    {return 1;} //défaite, aucuns items identiques.
    return 0; //no gair nor loss
}

void affichage_results(int resultat, float benefice){
        switch (resultat)
        {
        case 0 : printf("Desole, erreur dans le tirage, vous n'avez rien perdu.\n");break;
        case 1 : printf("Vous avez perdu...\n");break;
        case 2 : printf("Bravo ! Vous avez gagné %.2f $ \n", benefice);break;
        case 3 : printf("JACKPOT!!!!!\nVous avez gagné %.2f $\n", benefice);break;
        default: break;
        }
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
    float profit;
    int choix;
    init_rouleaux();

    clear_terminal();
    if (stack<mise_mini){
        printf("Vous n'avez pas assez d'argent, allez à la banque.(o)\n");
        scanf("%s",&reponse);
        return stack;}

    printf("Début du jeu de la machine à sous ! \n Vous avez %.2f $ \n", stack);
    affichage_stack(stack);

    printf("Choisissez une action.\n\n");
    printf("0: Retourner au lobby.\n");
    printf("1: Jouer à la machine à sous.\n");
    scanf("%d",&choix);
    switch (choix)
    {
    case 0: clear_terminal(); printf("Merci d'être venu(e)!"); return stack; break;
    case 1: break;
    default:break;
    }

    while (true){
        clear_terminal();
        affichage_stack(stack);
        playerbet = mise_joueur();
        playerbet = cas_conformite(mise_conforme(playerbet,stack),playerbet,stack);
        stack -= playerbet;
        clear_terminal();
        affichage_stack(stack);
        printf("Votre mise est de %.f $ \n", playerbet);
        printf("Tirer pour lancer la machine à sous! (t)\n");
        char tirage;
        scanf("%s",&tirage);
        clear_terminal();
        init_aleatoire();
        printf("\n");

        // AFFICHAGE DE LA MACHINE A SOUS
        for (int j=0; j<5; j++){
        for (int i = 0; i< nombre_rouleaux; i++)
        {
            rouleaux[i].item = tirage_slot();
        }
        printf("%-20s |%-20s |%-20s |\n",affichage_item(0), affichage_item(1), affichage_item(2));
        sleep(0.1);
        }
        // MACHINE A SOUS 

        profit = gain(playerbet, check_results());
        stack += profit;
        affichage_results(check_results(),profit);

        printf("\n\n");
        affichage_stack(stack);
        printf("Votre nouveau stack est %.2f $ \n", stack);
        printf("\n\n\n\n\n");
        printf("Voulez vous continuer à jouer ? (o/n)\n");
        scanf("%s", &reponse);
        
        if(reponse[0]=='o'||reponse[0]=='O')//on regarde le premier cara de la chaine
            {
            if(stack<mise_mini){
                clear_terminal();
                affichage_stack(stack);
                printf("Plus assez d'argent, retournez à la banque pour deposer des $!!(o)\n");
                //sleep(4);
                scanf("%s",&reponse);
                return stack; break;
                }
            //stack suffisant : on continue dans la boucle de jeu
            }
        else { return stack; break;} //on retourne au lobby avec le return / sortie de la boucle
    } 
}  