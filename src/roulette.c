#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RED 0
#define BLACK 1

int main() {
    int balance = 1000;
    int bet;
    int number;
    int color;
    int tier;

    srand(time(0));

    printf("Bienvenue à la roulette du casino ! Votre solde initial est de 1000 $.\n");

    while (balance > 0) {
        printf("Solde actuel : %d $\n", balance);

        do {
            printf("Placez votre mise (0 pour quitter) : ");
            scanf("%d", &bet);
            if (bet < 0 || bet > balance) {
                printf("Mise invalide. Veuillez entrer une mise valide.\n");
            }
        } while (bet < 0 || bet > balance);

        if (bet == 0) {
            break;
        }

        printf("Choisissez un type de mise :\n");
        printf("1. Chiffre spécifique\n");
        printf("2. Rouge\n");
        printf("3. Noir\n");
        printf("4. Tiers (1-12, 13-24, 25-36)\n");

        int betType;
        scanf("%d", &betType);

        switch (betType) {
            case 1:
                do {
                    printf("Choisissez un numéro (0-36) : ");
                    scanf("%d", &number);
                } while (number < 0 || number > 36);
                break;
            case 2:
                color = RED;
                break;
            case 3:
                color = BLACK;
                break;
            case 4:
                do {
                    printf("Choisissez un tiers (1, 2, 3) : ");
                    scanf("%d", &tier);
                } while (tier < 1 || tier > 3);
                break;
            default:
                printf("Type de mise invalide.\n");
                continue;
        }

        int winningNumber = rand() % 37;

        printf("La roulette tourne... Le numéro gagnant est : %d\n", winningNumber);

        if (betType == 1) {
            if (number == winningNumber) {
                printf("Vous avez gagné en choisissant le numéro %d !\n", number);
                balance += bet * 35;  
            } else {
                printf("La maison gagne !\n");
                balance -= bet;
            }
        } else if (betType == 2 || betType == 3) {
            if ((winningNumber % 2 == 0 && betType == 2) || (winningNumber % 2 == 1 && betType == 3)) {
                printf("Vous avez gagné en misant sur %s !\n", (betType == 2) ? "le rouge" : "le noir");
                balance += bet;
            } else {
                printf("La maison gagne !\n");
                balance -= bet;
            }
        } else if (betType == 4) {
            int tierStart = (tier - 1) * 12 + 1;
            int tierEnd = tier * 12;
            if (winningNumber >= tierStart && winningNumber <= tierEnd) {
                printf("Vous avez gagné en misant sur le tiers %d !\n", tier);
                balance += bet * 3;  
            } else {
                printf("La maison gagne !\n");
                balance -= bet;
            }
        }
    }

    printf("Votre solde final est de %d $. Merci d'avoir joué !\n", balance);

    return 0;
}
