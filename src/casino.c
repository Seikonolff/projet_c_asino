#include "casino.h"
#include "poker.h"
#include "blackjack.h"
#include "slots.h"
#include "roulette.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //pour sleep (en secondes)
#include "database.h"

#define negative -1
//ajout de la possibilité de braquage
Player player;

void initialize_casino()
{
    printf("  _ _ _  ___  _    ___  ___  __ __  ___   ___  ___   ___  _ _  ___   ___  ___  ___  _  _ _  ___  \n");
    printf(" | | | || __>| |  |  _>| . ||  |  || __> |_ _|| . | |_ _|| | || __> |  _>| . |/ __>| || | || . | \n");
    printf(" | | | || _> | |_ | <__| | ||     || _>   | | | | |  | | |   || _>  | <__|   ||__ || ||   || | | \n");
    printf(" |__/_/ |___>|___|`___/`___'|_|_|_||___>  |_| `___'  |_| |_|_||___> `___/|_|_|<___/|_||_|_|`___'\n");

    printf("Veuillez entrer votre nom\n");
    scanf("%s", &player.name);
    player.credits = 0;
    arrivee_joueur(player.name, &player.credits);
    return;
}

int lobby()
{
    clear_terminal();
    affichage_stack(player.credits);
    printf("Bonjour %s,\nVous avez %2.f $.\n",player.name, player.credits);
    printf("\nVeuillez sélectionner un jeu :\n1: Poker\n2: Blackjack\n3: Machine à sous\n4: Roulette\n5: Aller a la banque\n6: Quitter\n");

        int choix;
        int valid_input = 0; // Introduce a boolean variable to track input validity
        do {
            if (scanf("%d", &choix) != 1) {
                // Si la saisie n'est pas un nombre
                printf("Veuillez entrer un numéro de jeu valide.\n");
                // Efface le tampon d'entrée pour éviter une boucle infinie en cas de saisie non numérique
                while (getchar() != '\n');
                continue;  // Retourne à la demande de mise
            }
            else {
                valid_input = 1; // Set the flag to true if the input is valid
            }
        } while (!valid_input);

            switch (choix) {
                case 1:
                    printf("Vous avez choisi Poker.\n");
                    player.credits = poker_game(player.credits);
                    break;
                case 2:
                    printf("Vous avez choisi Blackjack.\n");
                    player.credits = blackjack_game(player.credits);
                    break;
                case 3:
                    printf("Vous avez choisi Machine à sous.\n");
                    player.credits = slots_game(player.credits);
                    if (player.credits == negative){player.credits = 0; update_player_credit(player.name, &player.credits); return 0;}
                    break;
                case 4:
                    printf("Vous avez choisi Roulette\n\n\n");
                    player.credits = roulette_game(player.credits);
                    break;
                case 5:
                    clear_terminal();
                    affichage_stack(player.credits);
                    printf("Vous avez choisi la banque.\n Veuillez saisir le montant du depot.\n");
                    float depot;
                    int valid_input = 0; // Introduce a boolean variable to track input validity
                    do {
                        if (scanf("%f", &depot) != 1 || depot <= 0) {
                            // If the input is not a valid number or is less than or equal to 0
                            printf("Veuillez saisir un montant valide et positif.\n");
                            // Clear the input buffer to avoid an infinite loop
                            while (getchar() != '\n');
                        } else {
                            valid_input = 1; // Set the flag to true if the input is valid
                        }
                    } while (!valid_input); // Continue the loop until valid_input is true
                    player.credits += depot;
                    break;
                case 6:
                    update_player_credit(player.name, &player.credits);
                    printf("Merci d'avoir joué! Au revoir!\n");
                    return 0;
                    break;
                default:
                    printf("Sélection non valide. Veuillez choisir entre 1 et 6.\n");
                    break;
            } 
    return 1;
}
