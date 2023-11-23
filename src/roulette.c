// Reste à faire 
// -------> V1.4 : Jouer à la roulette française avec un seul joueur mais en pouvant faire plusieurs paris sur un même tirage.
// -------> V2: Modelisation graphique.


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

int lastWinningNumbers[MAX_NUMBERS_STORED] = {0};

void Affichage_lastsnums(){ //Merci Norman pour la fonction 
    printf("%95.s", " ");
    printf("+-------------------------------+\n");
    printf("%95.s", " ");
    printf("Derniers numéros: ");
    for (int i = 0; i < MAX_NUMBERS_STORED; i++) {
        if (lastWinningNumbers[i] != 0) {
            printf("%d ", lastWinningNumbers[i]);
        } else {
            printf("X "); 
        }
    }
    printf("\n");
    printf("%95.s", " ");
    printf("+-------------------------------+\n");
    printf("\n \n");
}

void RouletteTable() {
    printf("     +------+------+------+------+------+------+------+------+------+------+------+------+--------+\n");
    printf("     |      MANQUE (1 a 18)      |          IMPAIR           |           ROUGE(r)        |  TIER  |\n");
    printf("+----+------+------+------+------+------+------+------+------+------+------+------+------+   1    |\n");
    printf("|    | 3(r) | 6(n) | 9(r) | 12(n)| 15(r)| 18(n)| 21(r)| 24(n)| 27(r)| 30(n)| 33(r)| 36(n)|--------+\n");
    printf("|    +------+------+------+------+------+------+------+------+------+------+------+------+  TIER  |\n");
    printf("| 0  | 2(n) | 5(r) | 8(n) | 11(n)| 14(r)| 17(n)| 20(n)| 23(r)| 26(n)| 29(n)| 32(r)| 35(n)|   2    |\n");
    printf("|    +------+------+------+------+------+------+------+------+------+------+------+------+        |\n");
    printf("|    | 1(r) | 4(n) | 7(r) | 10(n)| 13(n)| 16(r)| 19(r)| 22(n)| 25(r)| 28(n)| 31(n)| 34(r)|--------+\n");
    printf("+----+------+------+------+------+------+------+------+------+------+------+------+------+  TIER  |\n");
    printf("     |      PASSE (19 a 36)      |           PAIR            |            NOIR(n)        |   3    |\n");
    printf("     +------+------+------+------+------+------+------+------+------+------+------+------+--------+\n");
}

void RouletteIntroTexte(){
    printf("######                                                        #####\n");
    printf("#     #  ####  #    # #      ###### ##### ##### ######       #     #   ##   #    # ######\n");
    printf("#     # #    # #    # #      #        #     #   #            #        #  #  ##  ## #\n");
    printf("######  #    # #    # #      #####    #     #   #####        #  #### #    # # ## # #####\n");
    printf("#   #   #    # #    # #      #        #     #   #            #     # ###### #    # #\n");
    printf("#    #  #    # #    # #      #        #     #   #            #     # #    # #    # #\n");
    printf("#     #  ####   ####  ###### ######   #     #   ######        #####  #    # #    # ######\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } // Vider le buffer d'entrée
}

int userbet(int balance) {
    int bet;
    bool valid_input;
    do {
        
        sleep (5);
        clear_terminal();
        printf("\n\n FAITES VOS JEUX! \n\n");
        Affichage_lastsnums(MAX_NUMBERS_STORED);
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
    printf("\n\n RIEN NE VA PLUS! \n\n");
    printf("La roulette tourne... Le numero gagnant est : %d\n", winningNumber);
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

void evaluateResult(int betType, int bet, int number, int color, int tier, int numCheval1, int numCheval2, int carreNum1, int carreNum2, int carreNum3, int carreNum4, int column, int columnsChoice, int lineChoice, int twoLinesChoice, int winningNumber, int *balance) {
    int win = 0;
    int firstNumInLine;
    int firstNumInTwoLines;
    int lastNumInTwoLines;

    switch (betType) {
        case 1:
            if (winningNumber == number) 
                {win = bet * 36;}
            break;

        case 2:
        case 3:
            if (color == getNumberColor(winningNumber)) 
                {win = bet * 1;}
            break;

        case 4:
            if ((tier == 1 && winningNumber >= 1 && winningNumber <= 12) ||
                (tier == 2 && winningNumber >= 13 && winningNumber <= 24) ||
                (tier == 3 && winningNumber >= 25 && winningNumber <= 36)) 
                {win = bet * 2;}
            break;

        case 5:
            if (winningNumber == numCheval1 || winningNumber == numCheval2) 
                {win = bet * 17;}
            break;

        case 6:
            if (winningNumber == carreNum1 || winningNumber == carreNum2 || winningNumber == carreNum3 || winningNumber == carreNum4) 
                {win = bet * 8;}
            break;

        case 7: 
            if ((column == 1 && winningNumber % 3 == 1) ||
                (column == 2 && winningNumber % 3 == 2) ||
                (column == 3 && winningNumber % 3 == 0 && winningNumber != 0)) 
                {win = bet * 2;}
            break;

        case 8: 
            if ((columnsChoice == 1 && (winningNumber % 3 == 1 || winningNumber % 3 == 2)) ||
                (columnsChoice == 2 && (winningNumber % 3 == 2 || (winningNumber % 3 == 0 && winningNumber != 0)))) 
                {win = bet * 0.5;}
            break;

        case 9: 
            firstNumInLine = (lineChoice - 1) * 3 + 1;
            if (winningNumber >= firstNumInLine && winningNumber < firstNumInLine + 3) 
                {win = bet * 11;}
            break;

        case 10: 
            firstNumInTwoLines = (twoLinesChoice - 1) * 3 + 1;
            lastNumInTwoLines = firstNumInTwoLines + 5; 
            if (winningNumber >= firstNumInTwoLines && winningNumber <= lastNumInTwoLines) 
                {win = bet * 5;}
            break;

        case 11:
            if (winningNumber >= 19 && winningNumber <= 36) 
                {win = bet * 1;}
            break;

        case 12:
            if (winningNumber >= 1 && winningNumber <= 18) 
                {win = bet * 1;}
            break;

        case 13:
            if (winningNumber != 0 && winningNumber % 2 == 0) 
                {win = bet * 1;}
            break;
        case 14:
            if (winningNumber != 0 && winningNumber % 2 != 0) 
                {win = bet * 1;}
            break;
    }

    if (win > 0) {
        printf("Vous avez gagne %d!\n", win);
        *balance += win;
    } else {
        printf("Vous avez perdu votre mise.\n");
        *balance -= bet;
    }

}

float roulette_game(float credits) {
    int balance = credits;
    int bet, betType;
    time_t start, end;
    float elapsed;
    srand((unsigned int)time(NULL));
    RouletteIntroTexte();
    printf("\n Bienvenue a la roulette! Vous avez %d pieces.\n", balance);                                                                                


    while (balance > 0) {
        
        bet = userbet(balance); // On suppose que userbet ne bloque pas et retourne immédiatement

        if (bet == 0) {
            break; // Sortie du jeu
        }
        start = time(NULL); // Commence le compte à rebours
        betType = getBetType(); // Demandez le type de pari après la mise
        end = time(NULL);
        elapsed += difftime(end, start);
        if (elapsed >= 30.0) {
            printf("\n\n RIEN NE VA PLUS! \n\n");
            printf("Temps ecoule pour choisir le type de pari! Retour au menu.\n");
            sleep(5);
            break; // Retour menu
        }
        int number = 0, color = 0, tier = 0, numCheval1 = 0, numCheval2 = 0, carreNum1 = 0, carreNum2 = 0, carreNum3 = 0, carreNum4 = 0; 
        int column = 0, twoColumnsChoice = 0, lineChoice = 0, twoLinesChoice = 0;

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
            case 7:
                column = getColumn();
                break;
            case 8:
                twoColumnsChoice = getTwoColumns();
                break;
            case 9:
                lineChoice = getLine();
                break;
            case 10:
                twoLinesChoice = getTwoLines();
            break;

        }

        int winningNumber = getWinningNumber();
            evaluateResult(betType, bet, number, color, tier, numCheval1, numCheval2, carreNum1, carreNum2, carreNum3, carreNum4, column, twoColumnsChoice, lineChoice, twoLinesChoice, winningNumber, &balance);
            printf("Votre solde est maintenant de %d pieces.\n", balance);
            elapsed = 0;
    }

    printf("Merci d'avoir joue a la roulette!\n\n");
    return balance;
}

