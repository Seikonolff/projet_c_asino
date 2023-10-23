#include <stdio.h>
#include "casino.h"
#include "poker.h"
#include "blackjack.h"
#include "slots.h"

int main() {

    int gameRunning = 1;
    while (gameRunning) {
        printf("Bienvenue au Casino!\n");
        printf("Selectionnez un jeu:\n1: Poker\n2: Blackjack\n3: Machine à sous\n4: Quitter\n");

        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Ajoutez la logique pour jouer au poker
                printf("Vous avez choisi Poker.\n");
                poker_game();
                break;
            case 2:
                // Ajoutez la logique pour jouer au blackjack
                printf("Vous avez choisi Blackjack.\n");
                blackjack_game();
                // Exemple: play_blackjack();
                break;
            case 3:
                // Ajoutez la logique pour jouer aux machines à sous
                printf("Vous avez choisi Machine à sous.\n");
                // Exemple: play_slots();
                break;
            case 4:
                printf("Merci d'avoir joué! Au revoir!\n");
                gameRunning = 0;
                break;
            default:
                printf("Sélection non valide. Veuillez choisir entre 1 et 4.\n");
                break;
        }
    }

    return 0;
}
