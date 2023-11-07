#include "casino.h"
#include "poker.h"
#include "blackjack.h"
#include "slots.h"
#include "roulette.h"
#include "stdio.h"
//#include "strcpy.h"

Player player;

void initialize_casino()
{
    printf("Bienvenue au Casino !\n");
    printf("Veuillez entrer votre credit\n");
    scanf("%f",&player.credits);
    //printf("%f\n",player.credits);
    //player.name += "";

    return;
}

int lobby()
{
    printf("Selectionnez un jeu:\n1: Poker\n2: Blackjack\n3: Machine à sous\n4: Roulette\n5: Quitter\n");

        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Vous avez choisi Poker.\n");
                player.credits = poker_game(player.credits);
                break;
            case 2:
                printf("Vous avez choisi Blackjack.\n");
                blackjack_game();
                break;
            case 3:
                printf("Vous avez choisi Machine à sous.\n");
                slots_game();
                break;
            case 4:
                printf("Vous avez choisi Roulette");
                player.credits = roulette_game(player.credits);
                break;
            case 5:
                printf("Merci d'avoir joue! Au revoir!\n");
                return 0;
                break;
            default:
                printf("Sélection non valide. Veuillez choisir entre 1 et 4.\n");
                break;
        }
    return 1;
}

void shutdown_casino() {
    // Nettoyage et libération des ressources avant la fermeture du programme
}
