#include "casino.h"

Player player;

void initialize_casinno()
{
    player.credits = 1000;
}

void start_game(GameType game_type)
{
    switch (game_type)
    {
    case POKER :
        /* code */
        break;
    
    case BLACKJACK :
        break;
    
    case SLOTS :
        break;
    
    default:
        break;
    }
}

void handle_game_logic() {
    // La logique du jeu serait gérée ici. Cela dépendra du jeu actuellement joué.
    // Vous pourriez avoir besoin de fonctions séparées pour la logique de chaque jeu.
}

void update_player_credits(int amount) {
    player.credits += amount;
    // Vous devez également gérer les cas où le joueur perd tous ses crédits
}

void shutdown_casino() {
    // Nettoyage et libération des ressources avant la fermeture du programme
}
