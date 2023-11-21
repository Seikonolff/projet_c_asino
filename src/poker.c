#include "poker.h"
#include "pokerhandranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DECK_SIZE 52

#define ROYAL_FLUSH    0
#define	STRAIGHT_FLUSH  1
#define	FOUR_OF_A_KIND  2
#define	FULL_HOUSE      3
#define	FLUSH           4
#define	STRAIGHT        5
#define	THREE_OF_A_KIND 6
#define	TWO_PAIR        7
#define	ONE_PAIR        8
#define	HIGH_CARD       9

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define CYA  "\x1B[36m"
#define WHT  "\033[37m"

int currentCardIndex = 0;

void initDeck(Card *deck)
{
    // initialiser le paquet
    for(int i = 0; i < 4; i++) 
    {
        for(int j = 0; j < 13; j++) { // pour chaque rang
            deck[i * 13 + j].suit = i;
            deck[i * 13 + j].value = j;
            deck[i * 13 + j].id = getCardIdentifier(i,j);
        }
    }
}
void shuffleDeck(Card *deck) 
{
    srand(time(NULL));  // initialisation de la séquence aléatoire
    for (int i = 0; i < DECK_SIZE - 1; i++) {
        int j = i + rand() / (RAND_MAX / (DECK_SIZE - i) + 1);
        Card temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

// fonction pour distribuer une main
void dealHands(Card *deck, Card *playerHand, Card *dealerHand) 
{
    for (int i = 0; i < 2; i++) 
    {
        playerHand[i] = deck[currentCardIndex++];
        dealerHand[i] = deck[currentCardIndex++];
    }
}

void dealBoard(Card *deck, Card *board) 
{
    for (int i = 0; i < 5; i++) 
    {
        board[i] = deck[currentCardIndex++];
    }
}

void printCards(const Card *board, int numCards, int hidden) 
{
    const char *suits[4] = {"♥", "♠", "♦", "♣"};
    const char *values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    // Imprime le haut de chaque carte
    for (int i = 0; i < numCards + hidden; i++) {
        printf("+-----+ ");
    }
    printf("\n");

    // Imprime la valeur et le haut de la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
    {
        printf("|"); // %-2s pour aligner les valeurs à gauche avec deux caractères
        printColored(values[board[i].value],suits[board[i].suit],1);
        printf("   | ");
    }

    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
    {
        printf("|  ");
        printColored(values[board[i].value],suits[board[i].suit],0);
        printf("  | ");
    }
    
    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime la valeur et le bas de la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
    {
        printf("|   "); // %-2s pour aligner les valeurs à gauche avec deux caractères
        printColored(values[board[i].value],suits[board[i].suit],1);
        printf("| ");
    }
    
    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime le bas de chaque carte
    for (int i = 0; i < numCards + hidden; i++) {
        printf("+-----+ ");
    }
    printf("\n");
}

void printHiddenCard(int numCards) 
{   
    for (int i = 0; i < numCards; i++) {
        printf("+-----+ ");
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < numCards; j++) {
            printf("|#####| ");
        }
        printf("\n");
    }
    for (int i = 0; i < numCards; i++) {
        printf("+-----+ ");
    }
    printf("\n");
}

void printDeck(Card deck[], int size) {
    const char *suits[4] = {"coeur", "pique", "carreau", "trefle"};
    const char *values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    for (int i = 0; i < size; i++) {
        printf("Card %d: %s of %s, ID: %d\n", i + 1, values[deck[i].value], suits[deck[i].suit], deck[i].id);
    }
}

void printStack(float stack_a_afficher)
{
    printf("%95.s", " ");
    printf("+--------------------+\n");
    printf("%95.s", " ");
    printf("|STACK: $%10.2f  |\n",stack_a_afficher);
    /*
    if(payout>0)
    {
        printf("%95.s", " ");
        printf("|        + $%6.2f|\n",payout);
        printf("%95.s", " ");
        printf("|          ----------|\n");
        printf("%95.s", " ");
        printf("|           $%6.2f|\n",stack_a_afficher + payout);
    }
    */
    printf("%95.s", " ");
    printf("+--------------------+\n");
    printf("\n \n");
}

void refreshDisplay(void)
{
    for(int i = 0; i < 100; i++)
    {
        printf("\n");
    }
}

void printBettingBoard(const Bets *bets) 
{ 
    printf("                                                                                               +--------------------+\n");
    printf("                                                                                               | BONUS | $%-9d |\n",bets->bonus);
    printf("                                                                                               | BLIND | $%-9d |\n",bets->blind);
    printf("                                                                                               | MISE  | $%-9d |\n",bets->bet);
    printf("                                                                                               | JOUER | $%-9d |\n",bets->play);
    printf("                                                                                               +--------------------+\n");

}

void printColored(const char *value, const char *suit, int type) //type = 1 pour print une value 0 pour une couleur
{
    const char *color;

    if(strcmp(suit, "♥") == 0)
        color = RED;
    else if (strcmp(suit, "♣") == 0)
        color = GRN;
    else if (strcmp(suit, "♦") == 0)
        color = CYA;
    else
        color = WHT;
    if(type)
        printf("%s%-2s\033[0m", color, value);
    else
        printf("%s%s\033[0m", color, suit);
        
}

void printRank(int rank, HandType type)
{
    const char* owner = (type == PLAYER) ? "Vous avez" : "Le dealer a";

    switch (rank)
    {
    case ROYAL_FLUSH:
        printf("%s une Quinte Royale !\n", owner);
        break;
    case STRAIGHT_FLUSH:
        printf("%s une Quinte Suité !\n", owner);
        break;
    case FOUR_OF_A_KIND:
        printf("%s un Carré !\n", owner);
        break;
    case FULL_HOUSE:
        printf("%s un Full !\n", owner);
        break;
    case FLUSH:
        printf("%s une Couleur !\n", owner);
        break;
    case STRAIGHT:
        printf("%s une Suite !\n", owner);
        break;
    case THREE_OF_A_KIND :
        printf("%s un Brelan !\n", owner);
        break;
    case  TWO_PAIR :
        printf("%s une double paire !\n", owner);
        break;
    case  ONE_PAIR :
        printf("%s une paire !\n", owner);
        break;
    case  HIGH_CARD :
        printf("%s une hauteur.\n", owner);
        break;
    default:
        printf("I'have never seen such combinaison in my life !\n");
        break;
    }
}

void printWelcome(void)
{
    printf(".------..------..------..------..------..------..------..------.        .------..------..------..------..------.\n");
    printf("|U.--. ||L.--. ||T.--. ||I.--. ||M.--. ||A.--. ||T.--. ||E.--. | .-.    |P.--. ||O.--. ||K.--. ||E.--. ||R.--. | .-.\n");
    printf("| (||) || :/|: || :/|: || (||) || (||) || (||) || :/|: || (||) |((5))   | :/|: || :||: || :||: || (||) || :(): |((5))\n");
    printf("| :||: || (__) || (__) || :||: || :||: || :||: || (__) || :||: | '-.-.  | (__) || :||: || :||: || :||: || ()() | '-.-.\n");
    printf("| '--'U|| '--'L|| '--'T|| '--'I|| '--'M|| '--'A|| '--'T|| '--'E|  ((1)) | '--'P|| '--'O|| '--'K|| '--'E|| '--'R|  ((1))\n");
    printf("`------'`------'`------'`------'`------'`------'`------'`------'   '-'  `------'`------'`------'`------'`------'   '-'  \n");
}

void displayGame(const Stage state, const Card *playerHand, const Bets playerBoard, const Card *dealerHand, const Card *board)
{
    refreshDisplay();
    switch (state)
    {
    case PREFLOP:
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHiddenCard(2);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printHiddenCard(5);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printCards(playerHand, 2, 0);
        printf("-----------------------------------------------------------------\n");
        printBettingBoard(&playerBoard);
        break;
    
    case FLOP:
        printf("Le 1er tour des enchères est passé, le flop est révélé \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHiddenCard(2);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printCards(board, 3, 2);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printCards(playerHand, 2, 0);
        printf("-----------------------------------------------------------------\n");
        printBettingBoard(&playerBoard);
        break;
    
    case TURNRIVER:
        printf("Le 2nd tour des enchères est passé, la turn et la river sont révélés \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHiddenCard(2);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printCards(board, 5, 0);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printCards(playerHand, 2, 0);
        printf("-----------------------------------------------------------------\n");
        printBettingBoard(&playerBoard);
        break;
    
    case REVEAL :
        printf("Les enchères sont terminées, les cartes du dealer sont revélées \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printCards(dealerHand, 2, 0);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printCards(board, 5, 0);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        if(playerBoard.hasFolded == 1)
            printHiddenCard(2);
        else
            printCards(playerHand, 2, 0);
        printf("-----------------------------------------------------------------\n");
        printBettingBoard(&playerBoard);
        break;
    
    default:
        break;
    }

}

float playerBet(Bets *playerBoard, const float playerStack, const Stage stage ) // Fonction qui se repète trop. Il faut changer la manière de faire
{
    int input;
    int inputBet;

    switch (stage)
    {
        case PREFLOP :
            if(playerStack < 4*playerBoard->bet)
            {
                printf("vous n'avez pas assez d'argent pour jouer.\n");
                return 0;
            }
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 3x ou 4x la mise de base.\n");
            printf("|| 0 pour ne pas check || 1 pour jouer 3x votre mise soit $%d || 2 pour jouer 4x votre mise soit $%d || \n", 3*playerBoard->bet, 4*playerBoard->bet);
            int input;
            do {
                scanf(" %d", &input);

                if (input < 0 || input > 2) {
                    printf("Entrée invalide. Veuillez entrer 0, 1 ou 2.\n");
                }
            } while (input < 0 || input > 2);
            
            switch (input)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    return 0;
                    break;
                case 1 :
                    playerBoard->play =  3*playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
                    playerBoard->hasBet = 1;
                    return 3*playerBoard->bet;
                    break;
                case 2 :
                    playerBoard->play =  4*playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
                    playerBoard->hasBet = 1;
                    return 4*playerBoard->bet;
                    break;
                default :
                    break;
            }
            break;

        case FLOP :
            if(playerStack < 2*playerBoard->bet)
            {
                printf("vous n'avez pas assez d'argent pour jouer.\n");
                return 0;
            }
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 2x la mise de base\n");
            printf("|| 0 pour check || ");
                if (playerBoard->hasBet == 0)
                    printf("1 pour jouer 2x votre mise soit $%d || ", 2 * playerBoard->bet);

            do {
                scanf(" %d", &input);

                if (input != 0 && input != 1) {
                    printf("Entrée invalide.\n");
                }
            } while (input != 0 && input != 1);
            switch (input)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    return 0;
                    break;
                case 1 :
                    if( playerBoard->hasBet == 0)
                    {
                        playerBoard->play =  2*playerBoard->bet;
                        playerBoard->hasBet = 1;
                        printf("vous avez joué $%d \n", playerBoard->play);
                        return 2*playerBoard->bet;
                        break;
                    }
                    else
                    {
                        printf("Option invalide.\n");
                        return 0;
                        break;
                    } 

                default :
                    break;
            }
            break;
        
        case TURNRIVER :
            printf("Voulez-vous jouer ? \n");
            printf("|| 0 pour check || ");
                if (playerBoard->hasBet == 0 && playerStack > playerBoard->bet)
                    printf("1 pour jouer 1x votre mise soit $%d || ", playerBoard->bet);
                
                printf("2 pour se coucher ||\n");
            do {
                scanf(" %d", &input);

                if (input < 0 || input > 2) {
                    printf("Entrée invalide.\n");
                }
            } while (input < 0 || input > 2);
            switch (input)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    return 0;
                    break;
                case 1 :
                    if( playerBoard->hasBet == 0 && playerStack > playerBoard->bet)
                    {
                        playerBoard->play =  playerBoard->bet;
                        playerBoard->hasBet = 1;
                        printf("vous avez joué $%d \n", playerBoard->play);
                        return playerBoard->bet;
                        break;
                    }
                    else
                    {
                        printf("Option invalide.\n");
                        return 0;
                        break;
                    }
                case 2 :
                    printf("Vous vous couchez\nBonne nuit...\n");
                    playerBoard->hasFolded = 1;
                    return 0;
                    break;
                default :
                    break;
            }
            break;
        
        default :
            printf("erreur lors de l'appel de la fonction playerBet\n");
            break;
    }
}

float gamePayout(const int playerHandValue, const int dealerHandValue, const Bets playerBoard)
{
    //tous les coefs ont été incrémentés de 1, on paye la mise selon son coef et on rend la mise 
    HandPayout payouts[] = {
        {501, 51},              //rang 0 : Quinte Flush Royale
        {51, 41},               //rang 1 : Quinte Flush
        {11, 31},               //rang 2 : Carré
        {4, 9},                 //rang 3 : Full
        {2.5, 8},               //rang 4 : Suite (Quinte)
        {2, 5},                 //rang 5 : Couleur (Flush)
        {0, 4},                 //rang 6 : Brelan
        {0, 0},                 //rang 7 : Double paire
        {0, 0},                 //rang 8 : Paire
        {0, 0}                  //rang 9 : Hauteur
    };

    //avant de faire quoi que ce soit on regarde si le joueur s'est couché
    if(playerBoard.hasFolded == 1)
    {
        printf("Vous vous êtes fold.\nVous récupérez votre mise de la case bonus.\n");
        return 0 + playerBoard.bonus;
    }

    int playerHandRank = hand_rank(playerHandValue);
    int dealerHandRank = hand_rank(dealerHandValue);

    printRank(playerHandRank, PLAYER);
    printRank(dealerHandRank, DEALER);

    if (playerHandRank < dealerHandRank) {
            printf("Le joueur gagne !\n");
            return 2*(playerBoard.bet + playerBoard.play) + playerBoard.blind*payouts[playerHandRank].blindMultiplier + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
        } else if (playerHandRank > dealerHandRank) {
            printf("Le dealer gagne !\n");
            return playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
        } else {
            if (playerHandValue > dealerHandValue)
            {
                printf("le dealer gagne a la hauteur !\n");
                return playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
            else if (playerHandValue < dealerHandValue)
            {
                printf("le joueur gagne a la hauteur !\n");
                return 2*(playerBoard.bet + playerBoard.play) + playerBoard.blind*payouts[playerHandRank].blindMultiplier + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
            else
            {
                printf("Le dealer et le joueur on la meme main !\n");
                return playerBoard.bet + playerBoard.play + playerBoard.blind + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
        }
}

float poker_game(float playerCredits)
{
    int pokerGame = POKER_ON;

    Card deck[DECK_SIZE];
    Card board[5];
    Card playerHand[2];
    Card dealerHand[2];
    Bets playerBoard;

    initDeck(deck);
    refreshDisplay();
    printWelcome();

    while(pokerGame == POKER_ON)
    {
        playerBoard.blind = 0;
        playerBoard.bet = 0;
        playerBoard.play = 0;
        playerBoard.bonus = 0;
        playerBoard.hasBet = 0;
        playerBoard.hasFolded = 0;
        currentCardIndex = 0;
        refreshDisplay();

        printStack(playerCredits);
        int maxBet = playerCredits/2 ; // Deux fois la valeur du stack
        int minBet = 10;
        int inputStatus;
        do {
            printf("Entrez votre mise (maximum $%d et minimum $%d) :\n", maxBet, minBet);
            inputStatus = scanf("%d", &playerBoard.bet);

            // Vider le buffer si la saisie n'est pas un nombre
            while (inputStatus != 1) {
                while (getchar() != '\n'); // Vider le buffer d'entrée
                printf("Veuillez entrer un nombre valide.\n");
                printf("Entrez votre mise (maximum %d) :\n", maxBet);
                inputStatus = scanf("%d", &playerBoard.bet);
            }

            if (playerBoard.bet > maxBet)
                printf("La mise ne peut pas dépasser deux fois la valeur de votre stack.\n");
            else if(playerBoard.bet < minBet)
                printf("La mise doit être supérieure à $%d \n", minBet);
        } while (playerBoard.bet > maxBet || playerBoard.bet < minBet);

        playerBoard.blind = playerBoard.bet;
        playerCredits -= 2*playerBoard.bet;
        refreshDisplay();
        printStack(playerCredits);
        printf("vous avez misé $%d, la blinde suit.\n", playerBoard.bet);

        char inputBonus;
        if(playerCredits != 0)
        {
            do 
            {
                printf("Voulez vous miser sur Bonus ? (o/n)\n");
                scanf(" %c", &inputBonus);
                if(inputBonus != 'o' && inputBonus != 'n')
                    printf("Entrée invalide. Veuillez réessayer.\n");
            }while(inputBonus != 'o' && inputBonus != 'n');

            if(inputBonus == 'o' )
            {
                printf("Veuillez saisir votre mise sur Bonus\n");
                int bonusBet;
                do 
                {
                    scanf("%d", &bonusBet);

                    if (bonusBet > playerCredits) {
                        printf("Vous ne pouvez pas miser plus de crédits que vous n'en avez !\n");
                    }
                } while (bonusBet > playerCredits);

                playerBoard.bonus = bonusBet;
                playerCredits -= bonusBet;
            }
        }
       
        Stage stage = PREFLOP;

        shuffleDeck(deck); // mélanger le paquet
        printDeck(deck, DECK_SIZE);
        printf("card index = %d\n", currentCardIndex);
        dealHands(deck, playerHand, dealerHand); // distribue les mains
        printf("card index = %d\n", currentCardIndex); 
        dealBoard(deck, board);
        printf("card index = %d\n", currentCardIndex);
        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        printStack(playerCredits);
        playerCredits -= playerBet(&playerBoard, playerCredits, stage);
        sleep(2);

        stage = FLOP;

        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        printStack(playerCredits);
        playerCredits -= playerBet(&playerBoard, playerCredits, stage);
        sleep(2);
        
        stage = TURNRIVER;

        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        printStack(playerCredits);
        playerCredits -= playerBet(&playerBoard, playerCredits, stage);
        sleep(2);
        
        stage = REVEAL;

        Card playerSevenCardHand[7];
        Card dealerSevenCardHand[7];

        // On copie les deux cartes du joueur et les cinq cartes du board dans le tableau de sept cartes
        memcpy(playerSevenCardHand, playerHand, sizeof(Card) * 2);
        memcpy(&playerSevenCardHand[2], board, sizeof(Card) * 5); 

        // On copie les deux cartes du dealer et les cinq cartes du board dans le tableau de sept cartes
        memcpy(dealerSevenCardHand, dealerHand, sizeof(Card) * 2); 
        memcpy(&dealerSevenCardHand[2], board, sizeof(Card) * 5); 

        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        sleep(3);
        printStack(playerCredits);
        float payout = gamePayout(eval_7hand(playerSevenCardHand, PLAYER), eval_7hand(dealerSevenCardHand, DEALER), playerBoard);

        playerCredits += payout; //il faut revoir si c'est necessaire ou comment améliorer cette partie
        if (payout > 0)
            printf("la banque vous crédite de %.2f \n",payout);
        else if (payout == 0)
            printf("Vous perdez $%d\n", playerBoard.bet + playerBoard.blind + playerBoard.bonus + playerBoard.play);
        printStack(playerCredits);
        sleep(2);

        if(playerCredits < 10 )
        {
            printf("Vous n'avez plus suffisament d'argent pour jouer !\n");
            sleep(2);
            printf("Allez donc vous refaire un virement vous voulez bien ?\n");
            sleep(2);
            pokerGame = POKER_OFF;
            return playerCredits;
        }
        
        printf("Voulez-vous rejouer ? (o/n)\n");
        char choixPoker;
        do 
            {
                scanf(" %c", &choixPoker);
                if(choixPoker != 'o' && choixPoker != 'n' && choixPoker != 'O' && choixPoker != 'N')
                    printf("Entrée invalide. Veuillez réessayer.");
            }while(choixPoker != 'o' && choixPoker != 'n' && choixPoker != 'O' && choixPoker != 'N');
        
        if(choixPoker == 'n' || choixPoker =='N')
        {
            pokerGame = POKER_OFF;
            return playerCredits;
        }
    }
    
}