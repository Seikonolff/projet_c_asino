// Reste à faire 
// ------->
// ------->

#include "roulette.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <slots.h>

#define RED 0
#define BLACK 1
#define GREEN 2
#define CARRE 6
#define LINE 9
#define TWO_LINES 10
#define PASSE 11
#define MANQUE 12
#define PAIR 13
#define IMPAIR 14
#define MAX_NUMBERS_STORED 3

#define ANSI_RED   "\x1B[31m"
#define ANSI_GREY "\x1B[30m"
#define ANSI_GREEN "\x1B[32m"
#define ANSI_WHITE "\033[37m"
#define ANSI_BLINK   "\x1B[5m"
#define ANSI_NOBLINK "\x1B[25m"


int lastWinningNumbers[MAX_NUMBERS_STORED] = {0};

// Structure
typedef struct {
    int betType;
    int betAmount;
    int specificNumber;
    int color;
    int tier;
    int numCheval1, numCheval2;
    int carreNum1, carreNum2, carreNum3, carreNum4;
    int column, twoColumnsChoice, lineChoice, twoLinesChoice;
} Bet;

Bet getUserBet(int balance) {
    Bet bet = {0};
    bet.betAmount = userbet(balance);

    if (bet.betAmount == 0) {
        return bet; // Pas de nouveau pari
    }

    bet.betType = getBetType();

    switch (bet.betType) {
        case 1: // Chiffre spécifique
            bet.specificNumber = getSpecificNumber();
            break;
        case 2: // Rouge
        case 3: // Noir
            bet.color = getColor(bet.betType);
            break;
        case 4: // Tiers
            bet.tier = getTier();
            break;
        case 5: // Cheval
            getChevalNumbers(&bet.numCheval1, &bet.numCheval2);
            break;
        case 6: // Carre
            getCarreNumbers(&bet.carreNum1, &bet.carreNum2, &bet.carreNum3, &bet.carreNum4);
            break;
        case 7: // Colonne
            bet.column = getColumn();
            break;
        case 8: // Deux colonnes
            bet.twoColumnsChoice = getTwoColumns();
            break;
        case 9: // Ligne
            bet.lineChoice = getLine();
            break;
        case 10: // Deux lignes
            bet.twoLinesChoice = getTwoLines();
            break;
        case 11: // Passe
        case 12: // Manque
        case 13: // Pair
        case 14: // Impair
            // Pas de détails supplémentaires requis pour ces paris
            break;
    }

    return bet;
}

void Display_LastNum_Balance(int balance) {
    printf("%90.s", " ");
    printf("+-------------------------------+\n");
    printf("%90.s", " ");
    printf("Solde actuel: %d\n", balance);
    printf("%90.s", " ");
    printf("+-------------------------------+\n");
    printf("%90.s", " ");
    printf("Derniers numéros: ");
    for (int i = 0; i < MAX_NUMBERS_STORED; i++) {
        if (lastWinningNumbers[i] != 0) {
            int color = getNumberColor(lastWinningNumbers[i]);

            if (color == RED) {
                printf(ANSI_RED "%d " ANSI_WHITE, lastWinningNumbers[i]);
            } else if (color == BLACK) {
                printf(ANSI_GREY "%d " ANSI_WHITE, lastWinningNumbers[i]);
            } else {
                printf(ANSI_GREEN "%d " ANSI_WHITE, lastWinningNumbers[i]);
            }

        } else {
            printf("X ");
        }
    }
    printf("\n");
    printf("%90.s", " ");
    printf("+-------------------------------+\n");
    printf("\n \n");
}

void RouletteTable() {
    printf("     +------+------+------+------+------+------+------+------+------+------+------+------+--------+\n");
    printf("     |      MANQUE (1 a 18)      |          IMPAIR           |           " ANSI_RED "ROUGE(r)" ANSI_WHITE "        |  TIER  |\n");
    printf("+----+------+------+------+------+------+------+------+------+------+------+------+------+   1    |\n");
    printf("|    | " ANSI_RED "3(r) " ANSI_WHITE "| " ANSI_GREY "6(n) " ANSI_WHITE "| " ANSI_RED "9(r) " ANSI_WHITE "| " ANSI_GREY "12(n)" ANSI_WHITE "| " ANSI_RED "15(r)" ANSI_WHITE "| " ANSI_GREY "18(n)" ANSI_WHITE "| " ANSI_RED "21(r)" ANSI_WHITE "| " ANSI_GREY "24(n)" ANSI_WHITE "| " ANSI_RED "27(r)" ANSI_WHITE "| " ANSI_GREY "30(n)" ANSI_WHITE "| " ANSI_RED "33(r)" ANSI_WHITE "| " ANSI_GREY "36(n)" ANSI_WHITE "|--------+\n");
    printf("|    +------+------+------+------+------+------+------+------+------+------+------+------+  TIER  |\n");
    printf("| " ANSI_GREEN "0  " ANSI_WHITE "| " ANSI_GREY "2(n) " ANSI_WHITE "| " ANSI_RED "5(r) " ANSI_WHITE "| " ANSI_GREY "8(n) " ANSI_WHITE "| " ANSI_GREY "11(n)" ANSI_WHITE "| " ANSI_RED "14(r)" ANSI_WHITE "| " ANSI_GREY "17(n)" ANSI_WHITE "| " ANSI_GREY "20(n)" ANSI_WHITE "| " ANSI_RED "23(r)" ANSI_WHITE "| " ANSI_GREY "26(n)" ANSI_WHITE "| " ANSI_GREY "29(n)" ANSI_WHITE "| " ANSI_RED "32(r)" ANSI_WHITE "| " ANSI_GREY "35(n)" ANSI_WHITE "|   2    |\n");
    printf("|    +------+------+------+------+------+------+------+------+------+------+------+------+        |\n");
    printf("|    | " ANSI_RED "1(r) " ANSI_WHITE "| " ANSI_GREY "4(n) " ANSI_WHITE "| " ANSI_RED "7(r) " ANSI_WHITE "| " ANSI_GREY "10(n)" ANSI_WHITE "| " ANSI_GREY "13(n)" ANSI_WHITE "| " ANSI_RED "16(r)" ANSI_WHITE "| " ANSI_RED "19(r)" ANSI_WHITE "| " ANSI_GREY "22(n)" ANSI_WHITE "| " ANSI_RED "25(r)" ANSI_WHITE "| " ANSI_GREY "28(n)" ANSI_WHITE "| " ANSI_GREY "31(n)" ANSI_WHITE "| " ANSI_RED "34(r)" ANSI_WHITE "|--------+\n");
    printf("+----+------+------+------+------+------+------+------+------+------+------+------+------+  TIER  |\n");
    printf("     |      PASSE (19 a 36)      |           PAIR            |            " ANSI_GREY "NOIR(n)" ANSI_WHITE "        |   3    |\n");
    printf("     +------+------+------+------+------+------+------+------+------+------+------+------+--------+\n");
}

void RouletteIntroTexte(){
    printf(ANSI_BLINK); // Début du clignotement
    printf("######                                                        #####\n");
    printf("#     #  ####  #    # #      ###### ##### ##### ######       #     #   ##   #    # ######\n");
    printf("#     # #    # #    # #      #        #     #   #            #        #  #  ##  ## #\n");
    printf("######  #    # #    # #      #####    #     #   #####        #  #### #    # # ## # #####\n");
    printf("#   #   #    # #    # #      #        #     #   #            #     # ###### #    # #\n");
    printf("#    #  #    # #    # #      #        #     #   #            #     # #    # #    # #\n");
    printf("#     #  ####   ####  ###### ######   #     #   ######        #####  #    # #    # ######\n");
    printf(ANSI_NOBLINK); // Fin du clignotement
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } // Vider le buffer d'entrée
}

int userbet(int balance) {
    int bet;
    bool valid_input;
    do {
        Display_LastNum_Balance(balance);
        RouletteTable();
        printf("Placez votre mise (0 pour quitter) : ");
        
        valid_input = scanf("%d", &bet);
        if (!valid_input) {
            printf("Entree invalide. Veuillez entrer un nombre.\n");
            clear_input_buffer(); 
            bet = -1; 
        } else if (bet < 0 || bet > balance) {
            printf("Mise invalide. Veuillez entrer une mise valide.\n");
        }
    } while (bet < 0 || bet > balance);
    return bet;
}

int getBetType() {
    int betType;
        bool valid_input;
    do {
        printf("Choisissez un type de mise :\n");
        printf("1.  Chiffre specifique\n");
        printf("2.  Rouge \n");
        printf("3.  Noir \n");
        printf("4.  Tiers (1-12, 13-24, 25-36)\n");
        printf("5.  Cheval (deux numeros adjacents)\n");
        printf("6.  Carre (quatre numeros en carre)\n");
        printf("7.  Colonne (premiere, deuxieme, troisieme)\n");
        printf("8.  Deux colonnes adjacentes\n");
        printf("9.  Ligne (trois numeros verticaux comme 1, 2, 3)\n");
        printf("10. Deux lignes adjacentes (par exemple 1,2,3 et 4,5,6)\n");
        printf("11. Passe (19 a 36)\n");
        printf("12. Manque (1 a 18)\n");
        printf("13. Pair\n");
        printf("14. Impair\n");
    valid_input = scanf("%d", &betType);
        if (!valid_input || betType < 1 || betType > 14) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 14.\n");
            clear_input_buffer();
            betType = -1; // Pour continuer la boucle
        }
    } while (betType < 1 || betType > 14);
    return betType;
}

int getSpecificNumber() {
    int number;
    bool valid_input;
    do {
        printf("Choisissez un numero (0-36) : ");
        valid_input = scanf("%d", &number);
        if (!valid_input || number < 0 || number > 36) {
            printf("Entree invalide. Veuillez entrer un nombre entre 0 et 36.\n");
            clear_input_buffer();
            number = -1; 
        }
    } while (number < 0 || number > 36);
    return number;
}

int getColor(int betType) {
    return (betType == 2) ? RED : BLACK;
}

int getTier() {
    int tier;
    bool valid_input;
    do {
        printf("Choisissez un tiers (1, 2, 3) : ");
        valid_input = scanf("%d", &tier);
        if (!valid_input || tier < 1 || tier > 3) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 3.\n");
            clear_input_buffer();
            tier = -1; 
        }
    } while (tier < 1 || tier > 3);
    return tier;
}

int getWinningNumber() {
    int winningNumber = rand() % 37;
    int color = getNumberColor(winningNumber);

    printf("\n\n RIEN NE VA PLUS! \n\n");
    printf("La roulette tourne... Le numero gagnant est : ");
    
    if (color == RED) {
        printf(ANSI_RED "%d" ANSI_WHITE, winningNumber);
    } else if (color == BLACK) {
        printf(ANSI_GREY "%d" ANSI_WHITE, winningNumber);
    } else {
        printf(ANSI_GREEN "%d" ANSI_WHITE, winningNumber);
    }

    printf("\n");

    // Stocker le dernier numéro gagnant
    for (int i = MAX_NUMBERS_STORED - 1; i > 0; i--) {
        lastWinningNumbers[i] = lastWinningNumbers[i - 1];
    }
    lastWinningNumbers[0] = winningNumber;

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
    bool valid_input;
    do {
        printf("Entrez le premier numero (1-36) : ");
        valid_input = scanf("%d", num1);
        if (!valid_input || *num1 < 1 || *num1 > 36) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 36.\n");
            clear_input_buffer();
            continue; 
        }

        printf("Entrez le deuxième numero (1-36) : ");
        valid_input = scanf("%d", num2);
        if (!valid_input || *num2 < 1 || *num2 > 36) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 36.\n");
            clear_input_buffer();
            *num1 = -1; 
            continue; 
        }
    } while (!areAdjacent(*num1, *num2) || *num1 < 1 || *num1 > 36 || *num2 < 1 || *num2 > 36);
}

void getCarreNumbers(int *num1, int *num2, int *num3, int *num4) {
    bool valid_input;
    bool isValidSquare = false;
    do {
        printf("Entrez le premier numero (bas gauche) du carre (1-32) : ");
        valid_input = scanf("%d", num1);
        if (!valid_input || *num1 < 1 || *num1 > 32) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 32.\n");
            clear_input_buffer();
            continue; 
        }

        // Vérifiez si le numéro est dans la dernière colonne ou la dernière rangée (où un carré ne peut pas être formé)
        bool isLastColumn = (*num1 % 3 == 0);
        bool isLastRow = *num1 > 32;
        isValidSquare = !isLastColumn && !isLastRow;
        
        if (!isValidSquare) {
            printf("Numero invalide pour un carre. Veuillez choisir un autre numero.\n");
            *num1 = -1; //réinitialiser le numéro pour répéter la boucle
        }
    } while (!isValidSquare);

    // Les numéros qui forment le carré sont déterminés par le premier numéro
    *num2 = *num1 + 1;
    *num3 = *num1 + 3;
    *num4 = *num1 + 4;
    
    printf("Vous avez choisi le carre : %d, %d, %d, %d\n", *num1, *num2, *num3, *num4);
}

int getColumn() {
    int column;
    bool valid_input;
    do {
        printf("Choisissez une colonne (1 pour la premiere, 2 pour la deuxieme, 3 pour la troisieme, du bas vers le haut) : ");
        valid_input = scanf("%d", &column);
        if (!valid_input || column < 1 || column > 3) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 3.\n");
            clear_input_buffer();
            column = -1; 
        }
    } while (column < 1 || column > 3);


    printf("Les numeros dans cette colonne sont : ");
    for (int i = column; i <= 36; i += 3) {
        printf("%d ", i);
    }
    printf("\n");
    return column;
}

int getTwoColumns() {
    int columnsChoice;
    bool valid_input;
    do {
        printf("Choisissez deux colonnes adjacentes (1 pour les colonnes 1 et 2, 2 pour les colonnes 2 et 3) : ");
        valid_input = scanf("%d", &columnsChoice);
        if (!valid_input || columnsChoice < 1 || columnsChoice > 2) {
            printf("Entree invalide. Veuillez entrer 1 ou 2.\n");
            clear_input_buffer();
            columnsChoice = -1; 
        }
    } while (columnsChoice < 1 || columnsChoice > 2);

    int startColumn = (columnsChoice == 1) ? 1 : 2;
    printf("Les numeros dans ces colonnes sont : ");
    for (int i = startColumn; i <= 36; i += 3) {
        printf("%d ", i);
        if (i + 3 <= 36) {
            printf("%d ", i + 3);
        }
    }
    printf("\n");
    return columnsChoice;
}

int getLine() {
    int line;
    bool valid_input;
    do {
        printf("Choisissez une ligne (1-12 de gauche a droite) : ");
        valid_input = scanf("%d", &line);
        if (!valid_input || line < 1 || line > 12) {
            printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 12.\n");
            clear_input_buffer();
            line = -1; 
        }
    } while (line < 1 || line > 12);
    
    int startNumber = (line - 1) * 3 + 1;
    printf("Vous avez choisi la ligne contenant les numeros: %d, %d, %d.\n", startNumber, startNumber + 1, startNumber + 2);
    return line;
}

int getTwoLines() {
    int twoLinesChoice;
    bool valid_input;
    do {
        printf("Choisissez deux lignes adjacentes (1-11: 1 = lignes 1-2, 2 = lignes 2-3, etc...) : ");
        valid_input = scanf("%d", &twoLinesChoice);
        if (!valid_input || twoLinesChoice < 1 || twoLinesChoice > 11) {
            printf("Entree invalide. Veuillez entrer un nombre entre 1 et 11.\n");
            clear_input_buffer();
            twoLinesChoice = -1; 
        }
    } while (twoLinesChoice < 1 || twoLinesChoice > 11);
    
    int startNumber = (twoLinesChoice - 1) * 3 + 1;
    printf("Vous avez choisi les lignes contenant les numeros: %d, %d, %d et %d, %d, %d.\n", 
           startNumber, startNumber + 1, startNumber + 2, 
           startNumber + 3, startNumber + 4, startNumber + 5);
    return twoLinesChoice;
}

void evaluateResult(Bet bet, int winningNumber, int *balance) {
    int win = 0;

    switch (bet.betType) {
        case 1: // Chiffre spécifique
            if (winningNumber == bet.specificNumber) 
                win = bet.betAmount * 36;
            break;

        case 2: // Rouge
        case 3: // Noir
            if (bet.color == getNumberColor(winningNumber)) 
                win = bet.betAmount * 2;
            break;

        case 4: // Tiers
            if ((bet.tier == 1 && winningNumber >= 1 && winningNumber <= 12) ||
                (bet.tier == 2 && winningNumber >= 13 && winningNumber <= 24) ||
                (bet.tier == 3 && winningNumber >= 25 && winningNumber <= 36)) 
                win = bet.betAmount * 3;
            break;

        case 5: // Cheval
            if (winningNumber == bet.numCheval1 || winningNumber == bet.numCheval2) 
                win = bet.betAmount * 17;
            break;

        case 6: // Carre
            if (winningNumber == bet.carreNum1 || winningNumber == bet.carreNum2 || 
                winningNumber == bet.carreNum3 || winningNumber == bet.carreNum4) 
                win = bet.betAmount * 8;
            break;

        case 7: // Colonne
            if ((bet.column == 1 && winningNumber % 3 == 1) ||
                (bet.column == 2 && winningNumber % 3 == 2) ||
                (bet.column == 3 && winningNumber % 3 == 0 && winningNumber != 0)) 
                win = bet.betAmount * 3;
            break;

        case 8: // Deux colonnes
            if ((bet.twoColumnsChoice == 1 && (winningNumber % 3 == 1 || winningNumber % 3 == 2)) ||
                (bet.twoColumnsChoice == 2 && (winningNumber % 3 == 2 || (winningNumber % 3 == 0 && winningNumber != 0)))) 
                win = bet.betAmount * 1.5;
            break;

        case 9: // Ligne
            int firstNumInLine = (bet.lineChoice - 1) * 3 + 1;
            if (winningNumber >= firstNumInLine && winningNumber < firstNumInLine + 3) 
                win = bet.betAmount * 11;
            break;

        case 10: // Deux lignes
            int firstNumInTwoLines = (bet.twoLinesChoice - 1) * 3 + 1;
            int lastNumInTwoLines = firstNumInTwoLines + 5;
            if (winningNumber >= firstNumInTwoLines && winningNumber <= lastNumInTwoLines) 
                win = bet.betAmount * 5;
            break;

        case 11: // Passe
            if (winningNumber >= 19 && winningNumber <= 36) 
                win = bet.betAmount * 2;
            break;

        case 12: // Manque
            if (winningNumber >= 1 && winningNumber <= 18) 
                win = bet.betAmount * 2;
            break;

        case 13: // Pair
            if (winningNumber != 0 && winningNumber % 2 == 0) 
                win = bet.betAmount * 2;
            break;

        case 14: // Impair
            if (winningNumber != 0 && winningNumber % 2 != 0) 
                win = bet.betAmount * 2;
            break;
    }

    if (win > 0) {
        printf("Seul les paris effectues entierement dans les 45 secondes sont pris en compte.\n");
        printf("Vous avez gagné %d! (soit votre mise initiale plus vos gains) \n", win);
        *balance += win;
    } else {
        printf("Vous avez perdu votre mise de %d.\n", bet.betAmount);
    }
}

float roulette_game(float credits) {
    int balance = credits;
    Bet bets[1000];
    int numBets;
    char playAgain;
    time_t start, end;
    float elapsed;
    srand(time(NULL));

    RouletteIntroTexte();
    printf("\nBienvenue à la roulette ! Vous avez %d pièces.\n", balance);
    sleep(4);
    printf("\n LA ROULETTE TOURNE TOUTE LES 45 SECONDES! \n");
    printf("\n\n FAITES VOS JEUX! \n\n");
    elapsed = 0;
    do {
        numBets = 0;

        // Collecte des paris
        do {
        start = time(NULL);
        Bet bet = getUserBet(balance);
        end = time(NULL);
        elapsed += difftime(end, start);  // Mise à jour du temps écoulé

        if (elapsed >= 45.0) {
            printf("\n\n RIEN NE VA PLUS! \n\n");
            printf("Temps écoulé pour choisir votre pari! Attendez le prochain pari.\n");
            sleep(3);
            break; // Retour au menu
        }

            if (bet.betAmount == 0) { 
                return balance;
            }

            if (bet.betAmount > 0) {
                bets[numBets++] = bet;
                balance -= bet.betAmount;
            }

            if (balance > 0 && numBets < 1000) {
                printf("Voulez-vous placer un autre pari ? (o/n) : ");
                scanf(" %c", &playAgain);
            } else {
                playAgain = 'n';
            }

        } while (playAgain == 'o' && balance > 0 && numBets < 1000);

        // Tirage et évaluation des paris
        if (numBets > 0) {
            int winningNumber = getWinningNumber();

            for (int i = 0; i < numBets; i++) {
                evaluateResult(bets[i], winningNumber, &balance);
            }
        }

        printf("Votre solde est maintenant de %d pièces.\n", balance);
        elapsed = 0;

        // Demander si le joueur veut rejouer
        if (balance > 0) {
            playAgain = 'o';
            sleep(4);
            clear_terminal();
            printf("\n\n FAITES VOS JEUX! \n\n");
        } else {
            printf("Votre solde est insuffisant pour continuer à jouer.\n");
            playAgain = 'n';
        }

    } while (playAgain == 'o' && balance > 0);

    return balance;
}
