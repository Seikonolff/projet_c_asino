#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RED 0
#define BLACK 1
#define GREEN 2
#define CARRE 6

void RouletteTable() {
    printf("+----+----+----+----+----+----+----+----+----+----+----+----+\n");
    printf("|  3 |  6 |  9 | 12 | 15 | 18 | 21 | 24 | 27 | 30 | 33 | 36 |\n");
    printf("+----+----+----+----+----+----+----+----+----+----+----+----+\n");
    printf("|  2 |  5 |  8 | 11 | 14 | 17 | 20 | 23 | 26 | 29 | 32 | 35 |\n");
    printf("+----+----+----+----+----+----+----+----+----+----+----+----+\n");
    printf("|  1 |  4 |  7 | 10 | 13 | 16 | 19 | 22 | 25 | 28 | 31 | 34 |\n");
    printf("+----+----+----+----+----+----+----+----+----+----+----+----+\n");
}

int userbet(int balance) {
    int bet;
    do {
        RouletteTable();
        printf("Placez votre mise (0 pour quitter) : ");
        
        scanf("%d", &bet);
        if (bet < 0 || bet > balance) {
            printf("Mise invalide. Veuillez entrer une mise valide.\n");
        }
    } while (bet < 0 || bet > balance);
    return bet;
}

int getBetType() {
    int betType;
    printf("Choisissez un type de mise :\n");
    printf("1. Chiffre spécifique\n");
    printf("2. Rouge\n");
    printf("3. Noir\n");
    printf("4. Tiers (1-12, 13-24, 25-36)\n");
    printf("5. Cheval (deux numéros adjacents)\n");
    printf("6. Carré (quatre numéros en carré)\n");
    scanf("%d", &betType);
    return betType;
}

int getSpecificNumber() {
    int number;
    do {
        printf("Choisissez un numéro (0-36) : ");
        scanf("%d", &number);
    } while (number < 0 || number > 36);
    return number;
}

int getColor(int betType) {
    return (betType == 2) ? RED : BLACK;
}

int getTier() {
    int tier;
    do {
        printf("Choisissez un tiers (1, 2, 3) : ");
        scanf("%d", &tier);
    } while (tier < 1 || tier > 3);
    return tier;
}

int getWinningNumber() {
    int winningNumber = rand() % 37;
    printf("La roulette tourne... Le numéro gagnant est : %d\n", winningNumber);
    return winningNumber;
}

int getNumberColor(int number) {
    if (number == 0) return GREEN;
    
    int redNumbers[18] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

    for (int i = 0; i < 18; i++) {
        if (number == redNumbers[i]) return RED;
    }

    return BLACK;
}

bool areAdjacent(int num1, int num2) {
    int table[3][12] = {
        {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36},
        {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35},
        {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34}
    };

    int i1, j1, i2, j2;
    i1 = j1 = i2 = j2 = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 12; j++) {
            if (table[i][j] == num1) {
                i1 = i;
                j1 = j;
            }
            if (table[i][j] == num2) {
                i2 = i;
                j2 = j;
            }
        }
    }

    if ((i1 == i2 && abs(j1 - j2) == 1) || (j1 == j2 && abs(i1 - i2) == 1)) {
        return true;
    }
    if (abs(i1 - i2) == 1 && abs(j1 - j2) == 1) {
        return true;
    }

    return false;
}

void getChevalNumbers(int *num1, int *num2) {
    do {
        printf("Entrez le premier numéro (1-36) : ");
        scanf("%d", num1);
        printf("Entrez le deuxième numéro (1-36) : ");
        scanf("%d", num2);
    } while (!areAdjacent(*num1, *num2));
}

void getCarreNumbers(int *num1, int *num2, int *num3, int *num4) {
    do {
        printf("Entrez le premier numéro (haut gauche) du carré (1-33) : ");
        scanf("%d", num1);
        *num2 = *num1 + 1;
        *num3 = *num1 + 3;
        *num4 = *num1 + 4;
    } while (!(*num1 <= 34 && areAdjacent(*num1, *num2) && areAdjacent(*num1, *num3) && areAdjacent(*num2, *num4) && areAdjacent(*num3, *num4)));
    
    printf("Vous avez choisi le carré : %d, %d, %d, %d\n", *num1, *num2, *num3, *num4);
}


void evaluateResult(int betType, int bet, int number, int color, int tier, int numCheval1, int numCheval2, int carreNum1, int carreNum2, int carreNum3, int carreNum4, int winningNumber, int *balance) {
    int win = 0;

    switch (betType) {
        case 1:
            if (winningNumber == number) {
                win = bet * 36;
            }
            break;
        case 2:
        case 3:
            if (color == getNumberColor(winningNumber)) {
                win = bet * 2;
            }
            break;
        case 4:
            if ((tier == 1 && winningNumber >= 1 && winningNumber <= 12) ||
                (tier == 2 && winningNumber >= 13 && winningNumber <= 24) ||
                (tier == 3 && winningNumber >= 25 && winningNumber <= 36)) {
                win = bet * 3;
            }
            break;
        case 5:
            if (winningNumber == numCheval1 || winningNumber == numCheval2) {
                win = bet * 18;
            }
            break;
        case 6:
            if (winningNumber == carreNum1 || winningNumber == carreNum2 || winningNumber == carreNum3 || winningNumber == carreNum4) {
                win = bet * 9;
            }
            break;
    }

    if (win > 0) {
        printf("Vous avez gagné %d!\n", win);
        *balance += win;
    } else {
        printf("Vous avez perdu votre mise.\n");
        *balance -= bet;
    }
}

void roulette_game() {
    int balance = 1000;

    printf("Bienvenue à la roulette! Vous avez %d pièces.\n", balance);

    while (balance > 0) {
        int bet = userbet(balance);
        if (bet == 0) break;

        int betType = getBetType();

        int number = 0, color = 0, tier = 0, numCheval1 = 0, numCheval2 = 0, carreNum1 = 0, carreNum2 = 0, carreNum3 = 0, carreNum4 = 0;

        switch (betType) {
            case 1:
                number = getSpecificNumber();
                break;
            case 2:
            case 3:
                color = getColor(betType);
                break;
            case 4:
                tier = getTier();
                break;
            case 5:
                getChevalNumbers(&numCheval1, &numCheval2);
                break;
            case 6:
                getCarreNumbers(&carreNum1, &carreNum2, &carreNum3, &carreNum4);
                break;
        }

        int winningNumber = getWinningNumber();
        evaluateResult(betType, bet, number, color, tier, numCheval1, numCheval2, carreNum1, carreNum2, carreNum3, carreNum4, winningNumber, &balance);

        printf("Votre solde est maintenant de %d pièces.\n", balance);
    }

    printf("Merci d'avoir joué à la roulette!");
}

