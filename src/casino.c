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
    printf("Vous avez %f $.\n", player.credits);
    printf("Selectionnez un jeu:\n1: Poker\n2: Blackjack\n3: Machine à sous\n4: Roulette\n5: Aller a la banque\n6: Quitter\n");

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
                player.credits = slots_game(player.credits);
                break;
            case 4:
                printf("Vous avez choisi Roulette");
                player.credits = roulette_game(player.credits);
                break;
            case 5:
                printf("Vous avez choisi la banque.\n Veuillez saisir le montant du depot.\n");
                float depot;
                scanf("%f", &depot);
                while(depot <= 0){
                    printf("Veuillez saisir un montal valide");
                    scanf("%f", &depot);
                }
                player.credits += depot;
                break;
            case 6:
                printf("Merci d'avoir joué! Au revoir!\n");
                return 0;
                break;
            default:
                printf("Sélection non valide. Veuillez choisir entre 1 et 6.\n");
                break;
        }
    return 1;
}

void shutdown_casino() {
    // Nettoyage et libération des ressources avant la fermeture du programme
}
