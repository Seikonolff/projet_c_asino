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
    //player.name += "";
    player.credits = 1000;
}

int lobby()
{
    printf("Bienvenue au Casino!\n");
    printf("Selectionnez un jeu:\n1: Poker\n2: Blackjack\n3: Machine à sous\n4: Roulette\n5: Quitter\n");

        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Vous avez choisi Poker.\n");
                start_game(POKER);
                //**
                // Pour que le joueur retrouve son stack dans sa partie de poker, il faudra passer le montant de son tapis à la fonction
                // player.credits = poker_game(player.credits);
                // La fonctionne retourne, à la fin de la partie, le montant du tapis mis à jour
                //**
                break;
            case 2:
                printf("Vous avez choisi Blackjack.\n");
                start_game(BLACKJACK);
                break;
            case 3:
                printf("Vous avez choisi Machine à sous.\n");
                start_game(SLOTS);
                break;
            case 4:
                printf("Vous avez choisi Roulette");
                start_game(ROULETTE);
                break;
            case 5:
                printf("Merci d'avoir joué! Au revoir!\n");
                return 0;
                break;
            default:
                printf("Sélection non valide. Veuillez choisir entre 1 et 4.\n");
                break;
        }
    return 1;
}

void start_game(GameType game_type) // à voir si on garde cette fonction elle peut très bien merger dans le switch case du lobby
{
    switch (game_type)
    {
    case POKER :
        poker_game();
        break;
    
    case BLACKJACK :
        blackjack_game();
        break;
    
    case SLOTS :
        break;

    case ROULETTE :
        roulette_game();
        break;
    
    default:
        break;
    }
}

void update_player_credits(int amount) {
    player.credits += amount;
}

void shutdown_casino() {
    // Nettoyage et libération des ressources avant la fermeture du programme
}
