
#include "slots.h"
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()
#include <stdio.h> // pour printf et scanf
#include <string.h> // pour strcpy
#include <unistd.h> //pour sleep (en secondes)
#include <math.h> //pour floor (arrondir a l'entier inférieur)
#include <windows.h>
#define nombre_item 4
#define probabilite_tirage 10
#define nombre_rouleaux 3
#define mise_mini_slots 10
#define true 1
#define false 0
#define negative -1
#define tailorface 2
#define recettes 8733

int cdl; //compteur de lose

enum ResultatJeu {
    ERREUR_TIRAGE = 0,
    DEFAITE = 1,
    DEUX_ITEMS_IDENTIQUES = 2,
    TROIS_ITEMS_IDENTIQUES = 3
};

slot rouleaux[nombre_rouleaux]; //définition d'un tableau rouleaux de 3 structures slot

char* item0; //définition de l'item du rouleau X

void clear_terminal(){ //Fonction pour nettoyer visuellement le terminal
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
    printf("\n");
}

float mise_joueur(){    //Fonction pour demander au joueur de miser
    float mise;
    printf("Combien voulez vous miser ?\n");
    do{
        if (scanf("%f", &mise) !=1)
            {printf("Veuillez entrer un montant valide.\n");
            while (getchar() != '\n');
            continue;
            }
        else 
            {return mise;}
        } 
    while (1);
    return 0;
}

float mise_conforme(float bet_joueur, float stack_joueur, float mise_mini_jeu){ //Fonction pour vérifier que la mise joueur est correcte
    int playerbet_int;
    playerbet_int = (int)bet_joueur;
    if (bet_joueur <= stack_joueur){        //comparaison si le joueur a assez d'argent pour miser sa mise
        if (bet_joueur >= mise_mini_jeu){   //comparaison à la mise minimale du jeu
            if (bet_joueur != playerbet_int){   // comparaison si le joueur mise des centimes
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

float cas_conformite(int cas_conforme, float bet_joueur_2, float stack_joueur2, float mise_mini_cas){ //Fonction de boucle pour vérifier les mises
    while (cas_conforme != 0){
        bet_joueur_2 = mise_joueur();
        cas_conforme = mise_conforme(bet_joueur_2, stack_joueur2, mise_mini_cas);
    }
    return bet_joueur_2;
    
}

void init_rouleaux()    //Initialise le nom des rouleaux (facultatif)
{
strcpy(rouleaux[0].nom_slot,"Rouleau 0");
strcpy(rouleaux[1].nom_slot, "Rouleau 1");
strcpy(rouleaux[2].nom_slot, "Rouleau 2");
}

void init_aleatoire()   //intialise le "temps" du module random
{
    srand(time(NULL));
}

int tirage_slot(int previous1, int previous2)   //définit un nombre pour chaque rouleau (un nmbre=un item)
{
    int similarite;
    int new_tirage;
    if (previous1 < 0)
        {return rand()%nombre_item;}
        
    similarite = rand()%probabilite_tirage;
    if (previous2 < 0)
    { 
        if (similarite==0)
            {return previous1;}
        else 
        {
            new_tirage = rand()%nombre_item;
            while (new_tirage == previous1)
            {
                new_tirage = rand()%nombre_item;
            }
            return new_tirage;
        }
    }
    else {
        if (similarite == 0)
            {
                if (rand()%tailorface == 0) {return previous1;}
                else {return previous2;}
            }
        else {
                new_tirage = rand()%nombre_item;
                while (new_tirage == previous1 || new_tirage == previous2)
                {
                    new_tirage = rand()%nombre_item;
                }
                return new_tirage;
        }
        }
}

void tirage_machine(float pari){    //affiche la machine a sous et effectue le tirage en fonction des items précedents tirés
        for (int i = 0; i< nombre_rouleaux; i++)
        {
            switch (i)
            {
                case 0: rouleaux[i].item = tirage_slot(negative,negative); break;
                case 1: rouleaux[i].item = tirage_slot(rouleaux[i-1].item, negative); break;
                case 2: rouleaux[i].item = tirage_slot(rouleaux[i-1].item, rouleaux[i-2].item); break;
                default: rouleaux[i].item = negative; break;
            }
        }
    char* item1 = "########";
    char* item2 = "########";
    char* item3 = "########";
    for (int k=0; k<3;k++){
        float gain_jeu;
        gain_jeu = 0;
        switch (k)
        {
        case 0: 
            item1 = affichage_item(0);
            break;
        case 1:
            item2 = affichage_item(1);
            break;
        case 2:
            item3 = affichage_item(2);
            gain_jeu = gain(pari, check_results());
            break;
        default:
            break;
        }
        printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢁⣠⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢀⣿⣿⣿⣿⡄⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠛⠛⠛⠀⠈⠉⠉⠉⠉⠁⠀⠛⠛⠛⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠋⣀⠀⠀⠤⠤⠦⠒⠚⠛⠛⠋⠉⠉⠉⠛⠛⠓⠒⠲⠤⠤⣀⣀⡈⠉⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠁⡀⠤⠖⠘⠉⣀⣀⣠⣤⣤⣶⣶⣾⣿⣿⣿⣿⣿⣿⣷⣶⣶⣦⣤⣄⣀⣀⠉⠛⠶⢤⣀⡈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⢽⣿⣿⣿⣿⡿⠛⠁⣠⠶⠋⢀⣠⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⣄⡈⠙⠢⣄⡀⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⢸⣿⣿⣿⠋⢀⣤⠎⠁⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡈⠻⣦⡀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⢸⠿⡟⠁⣠⠞⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⠈⠻⣄⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠞⠎⠀⣴⠏⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠙⣇⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⡟⠀⢸⡏⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⢹⣇⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⡇⢀⣿⠀⢸⣿⣿⡿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⠿⡇⠀⣿⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠀⠾⠿⠤⠶⠶⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠤⠿⠇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠄⠀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠄⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⠟⠉⢁⣀⣈⠉⠉\n");
        printf("⠂⠀⢏⠀⢰⣶⣶⣶⣶⣖⣶⣶⣶⣶⣶⣶⣖⣶⣶⣄⡲⣶⣶⣶⣶⣶⣶⣶⣶⣶⣖⣶⣶⣔⣲⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣀⠀⣿⠀⢸⣿⣿⣿⠃⢀⣾⣿⣿⣿⣷⠀\n");
        printf("⠀⠀⢸⠀⢸⣿⡭⠍⠉⢉⣁⣈⣉⣉⣉⣁⣁⣀⠈⠹⣵⠀⢉⣉⣉⣉⣉⣉⣉⣀⣁⡀⠈⣭⡅⠀⣉⣉⣉⣉⣉⣉⣉⣉⣉⡉⠉⣿⣿⣏⠀⣿⠀⢸⣿⣿⣧⠀⢿⣿⣿⣿⣿⣿⠀\n");
        printf("⠀⠀⣿⠀⢸⣿⡇⡆⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢠⣾⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣷⣷⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⣄⠈⢿⣿⣿⣿⡿⠀\n");
        printf("⡀⠀⣹⠀⢸⣿⣿⡇⢸%-8s⢸ ⢘⢸ ⢸%-8s⢸ ⣿⣿ ⡇%-8s⢸ ⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⡏⠀⠀⢸⣿⣿⣿⣿\n",item1, item2, item3);
        printf("⠄⠀⣹⠀⢸⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⢸ ⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣹⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⡀⠀⠀⣿⣿⣿⣿⣿\n");
        printf("⡄⠀⣿⠀⢸⣿⣿⡆⠀⠛⠛⠛⠛⠛⠛⠛⠛⠃⠀⢸⣿⠀⠘⠛⠛⠛⠛⠛⠛⠛⠛⠂⠀⣼⣿⠀⠙⠛⠛⠛⠛⠛⠛⠛⠛⠁⠀⣿⣿⣿⠀⣿⠀⢸⣿⣿⡇⠀⠀⣿⣿⣿⣿⣿⣿\n");
        printf("⠆⠀⣿⠀⠸⠛⠛⠿⠆⠒⠒⠒⠒⠖⠶⠶⠶⠶⠶⠿⠿⠷⠖⠲⠶⠶⠶⠶⠶⠶⠶⠶⠶⠛⠻⠿⠶⠶⠶⠶⠶⠶⠶⠶⠾⠿⠿⠿⠿⠟⠀⣻⠀⢸⣿⣿⠀⠀⢀⣿⣿⣿⣿⣿⣿\n");
        printf("⠁⠀⣿⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣿⠀⢸⣿⡏⠀⠀⢸⣿⣿⣿⣿⣿⣿\n");
        printf("⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢰⣶⣶⡆⠀⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠂⠀⣿⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⣿⠀⢸⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⡁⠀⣿⠀⢰⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⠀⣿⠀⠘⠿⠿⠇⠨⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠂⠀⣿⠀⢸⣿⣿⣿⡟⠉⠻⣿⣿⣿⣿⣿⣿⡟⠉⢻⣿⣿⣿⣿⣿⣿⠏⠙⣿⣿⣿⣿⣿⣿⡿⠉⠹⣿⣿⣿⣿⣿⣿⡟⠉⢻⣿⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠀⠀⣿⠀⢸⣿⠈⠙⠁⢀⠀⠉⠛⠛⠋⠉⠉⠀⠀⠈⠉⠛⢻⠛⠉⠁⢀⡀⠈⠙⠛⠉⠙⠉⠁⢀⠀⠉⠙⠛⠟⠛⠉⠀⡄⠈⠉⠛⢻⣿⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠀⠀⣿⠀⢸⣿⣦⠀⠸⠯⠇⠀⣠⣾⣶⣀⠈⠹⠿⠍⠀⣴⣿⣦⡀⠈⠿⢟⠀⢠⣶⣷⣤⠀⠘⠿⠟⠀⢠⣾⣶⣄⠈⢹⠿⠃⠀⣴⣿⣿⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠄⠀⣿⠀⢸⣿⣿⠀⢀⣀⡀⠀⢻⣿⣿⣟⠀⣀⣀⡀⠀⣿⣿⣿⡇⠀⣀⣀⠀⠘⣿⣿⣿⠁⢀⣀⡀⠀⢸⣿⣿⣿⠀⢀⣀⡀⠀⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⡂⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⡇⠀⣿⣀⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣉⣁⣀⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠄⠀⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠂⠀⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⡆⠀⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⠀⢰⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("  ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇ ⣿GAIN : %9.2f⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n",gain_jeu);
        printf("⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        printf("⠄⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n");
        if (k<2){
            sleep(2);
            clear_terminal();
        }
    }
}

char* affichage_item(int rouleau)   //affiche l'item tiré des rouleaux
{
    switch(rouleaux[rouleau].item)
        {
            case 0: {item0="  BELL  ";return item0;}
            case 1: {item0="   BAR  ";return item0;}
            case 2: {item0="CHERRIES";return item0;}
            case 3: {item0="    7   ";return item0;}
            default: {item0=" ERREUR ";return item0;}
        }
}

int check_results()    //vérifie la situation en fonction du tirage 
{
    for (int j=0; j<3; j++){
        if (affichage_item(j) == "ERREUR") //strcmp renvoie 0 si les deux chaines sont identiques
            {return ERREUR_TIRAGE;}
        }
    if (rouleaux[0].item == rouleaux[1].item && rouleaux[1].item == rouleaux[2].item)
    {return TROIS_ITEMS_IDENTIQUES;} //jackpot, 3 items identiques

    if (rouleaux[0].item == rouleaux[1].item || rouleaux[1].item == rouleaux[2].item || rouleaux[2].item == rouleaux[0].item)
    {return DEUX_ITEMS_IDENTIQUES;} // 2 items identiques 

    if (rouleaux[0].item != rouleaux[1].item && rouleaux[1].item != rouleaux[2].item && rouleaux[2].item != rouleaux[0].item)
    {return DEFAITE;} //défaite, aucuns items identiques.
    
    return 0; //no gair nor loss
}

void affichage_results(int resultat, float benefice){   //affiche les résultats au joueur
        switch (resultat)
        {
        case 0 : printf("Desole, erreur dans le tirage, vous n'avez rien perdu.\n");break;
        case 1 : printf("Vous avez perdu...\n");break;
        case 2 : printf("Bravo ! Vous avez gagné %.2f $ \n", benefice);break;
        case 3 : printf("JACKPOT!!!!!\nVous avez gagné %.2f $\n", benefice);break;
        default: break;
        }
}

float gain(float mise, int resultat){   //renvoie le gain associé au tirage/résultat
    switch (resultat)
    {
    case 0 : return mise; break; //cas d'une erreur lors du tirage
    case 1 : return 0; break;    //défaire du joueur
    case 2 : return 1.5*mise; break; //half house soit 2 item identiques
    case 3 : return 10*mise; break; //trois items identiques
    default: return mise; break;   //par défaut, erreur machine donc le joueur perd rien
    }
}

float slots_game(float stack)       //boucle principale du jeu
{
    char reponse[10];
    float playerbet;
    float profit;
    int choix;
    init_rouleaux();

    clear_terminal();
    if (stack<mise_mini_slots){
        printf("Vous n'avez pas assez d'argent, allez à la banque.\n");
        sleep(3);
        return stack;}

    printf("Début du jeu de la machine à sous ! \n Vous avez %.2f $ \n", stack);
    affichage_stack(stack);

    printf("Choisissez une action.\n\n");
    printf("0: Retourner au lobby.\n");
    printf("1: Jouer à la machine à sous.\n");

    do
    {
        if (scanf("%d", &choix) != 1){
            printf("Erreur de saisie, veuillez recommencer.\n");
            while(getchar() != '\n');
            continue;
        }
        else {
            break;
        }

    } while (1);

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
        playerbet = cas_conformite(mise_conforme(playerbet,stack, mise_mini_slots),playerbet,stack,mise_mini_slots);
        stack -= playerbet;
        clear_terminal();
        affichage_stack(stack);
        printf("Votre mise est de %.f $ \n", playerbet);
        printf("Tirer pour lancer la machine à sous! (t)\n");
        char tirage;
        scanf("%s",&tirage);
        clear_terminal();
        init_aleatoire();
        // AFFICHAGE DE LA MACHINE A SOUS
        tirage_machine(playerbet);
        // MACHINE A SOUS 
        profit = gain(playerbet, check_results());
        stack += profit;
        affichage_results(check_results(),profit);
        affichage_stack(stack);
        if (check_results()==1){cdl += 1;}
        else{cdl = 0;}
        if (cdl > 4){
            printf("Vous avez perdu %d fois de suite, vous vous enervez...\n", cdl);
            printf("Frapper la machine à sous ? (o/n)\n");
            char frapper[10];
            scanf("%s",&frapper);
            if(frapper[0]=='o'||frapper[0]=='O')//on regarde le premier cara de la chaine
            {
                printf("Le patron du casino vous voit frapper la machine...\nLes vigiles arrivent.\n Insulter les vigiles ? (o/n)\n");
                scanf("%s", &frapper);
                if(frapper[0]=='o'||frapper[0]=='O')
                {
                    printf("Les vigiles s'énervent et vous vous faites virer du casino. Vous perdez tout votre argent...\n");
                    stack = negative;
                    sleep(5);
                    return stack;
                }
                if (strcmp(frapper,"braquer")==0){
                    printf("Vous sortez un flingue et braquez les vigiles.\nVous arrivez à prendre les recettes du jour.... 8733$ et vous quittez la machine à sous...\n");
                    stack += recettes;
                    sleep(5);
                    return stack;
                }
                else {printf("Le patron du casino vous dit : 'ça va pour cette fois mais ne recommencez pas...'\n");}
            }
            cdl = 0;
        }
        printf("Voulez vous continuer à jouer ? (o/n)\n");
        scanf("%s", &reponse);
        
        if(reponse[0]=='o'||reponse[0]=='O')//on regarde le premier cara de la chaine
            {
            if(stack<mise_mini_slots){
                clear_terminal();
                affichage_stack(stack);
                printf("Plus assez d'argent, retournez à la banque pour deposer des $!!\n");
                sleep(4);
                cdl = 0;
                return stack; break;
                }
            //stack suffisant : on continue dans la boucle de jeu
            }
        else { cdl = 0; return stack; break;} //on retourne au lobby avec le return / sortie de la boucle
    } 
}  