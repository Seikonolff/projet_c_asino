#include "poker.h"
#include "pokerhandranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int currentCardIndex = 0;

void initDeck(Card *deck)
{
    // initialiser le paquet
    for(int i = 0; i < 4; i++) 
    {
        for(int j = 0; j < 13; j++) { // pour chaque rang
            deck[i * 13 + j].suit = i;
            deck[i * 13 + j].value = j;
            deck[i * 13 + j].id = getCardIdentifier(j , i);
        }
    }
}
void shuffleDeck(Card *deck) {
    srand(time(NULL));  // initialisation de la séquence aléatoire
    for (int i = 0; i < DECK_SIZE - 1; i++) {
        int j = i + rand() / (RAND_MAX / (DECK_SIZE - i) + 1);
        Card temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

// fonction pour distribuer une main
void dealHand(Card *deck, PokerHand *hand) {
    for (int i = 0; i < 2; i++) {
        hand->cards[i] = deck[currentCardIndex++];
    }
}

void dealBoard(Card *deck, Card *board, int numCards) {
    for (int i = 0; i < numCards; i++) {
        board[i] = deck[currentCardIndex++];
    }
}

void printHand(const PokerHand *hand) 
{
    //const char *suits[4] = {"H", "S", "D", "C"};
    const char *suits[4] = {"♥", "♠", "♦", "♣"};
    const char *values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

    // Imprime le haut de chaque carte
    for (int i = 0; i < 2; i++) {
        printf("+-----+ ");
    }
    printf("\n");

    // Imprime la valeur et le haut de la couleur de chaque carte
    for (int i = 0; i < 2; i++) {
        printf("|%-2s   | ", values[hand->cards[i].value]); // %-2s pour aligner les valeurs à gauche avec deux caractères
    }
    printf("\n");

    // Imprime la couleur de chaque carte
    for (int i = 0; i < 2; i++) {
        printf("|  %s  | ", suits[hand->cards[i].suit]);
    }
    printf("\n");

    // Imprime la valeur et le bas de la couleur de chaque carte
    for (int i = 0; i < 2; i++) {
        printf("|   %-2s| ", values[hand->cards[i].value]); // %-2s pour aligner les valeurs à gauche avec deux caractères
    }
    printf("\n");

    // Imprime le bas de chaque carte
    for (int i = 0; i < 2; i++) {
        printf("+-----+ ");
    }
    printf("\n");
}

// Imprime le haut de chaque carte cachée
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

void printBoard(const Card *board, int numCards, int hidden) {
    //const char *suits[4] = {"H", "S", "D", "C"};
    const char *suits[4] = {"♥", "♠", "♦", "♣"};
    const char *values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

    // Imprime le haut de chaque carte
    for (int i = 0; i < numCards + hidden; i++) {
        printf("+-----+ ");
    }
    printf("\n");

    // Imprime la valeur et le haut de la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
        printf("|%-2s   | ", values[board[i].value]); // %-2s pour aligner les valeurs à gauche avec deux caractères

    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
        printf("|  %s  | ", suits[board[i].suit]);
    
    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime la valeur et le bas de la couleur de chaque carte
    for (int i = 0; i < numCards; i++)
        printf("|   %-2s| ", values[board[i].value]); // %-2s pour aligner les valeurs à gauche avec deux caractères
    
    for (int i = 0; i < hidden; i++)
        printf("|#####| ");
    printf("\n");

    // Imprime le bas de chaque carte
    for (int i = 0; i < numCards + hidden; i++) {
        printf("+-----+ ");
    }
    printf("\n");
}

void refreshDisplay(void)
{
    for(int i = 0; i < 30; i++)
    {
        printf("\n");
    }
}

void displayGame(const Stage state, const PokerHand playerHand, const Bets playerBoard, const PokerHand dealerHand, const Card *board)
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
        printHand(&playerHand);
        printf("-----------------------------------------------------------------\n");
        break;
    
    case FLOP:
        printf("Le 1er tour des enchères est passé, le flop est révélé \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHiddenCard(2);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printBoard(board, 3, 2);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printHand(&playerHand);
        printf("-----------------------------------------------------------------\n");
        break;
    
    case TURNRIVER:
        printf("Le 2nd tour des enchères est passé, la turn et la river sont révélés \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHiddenCard(2);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printBoard(board, 5, 0);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printHand(&playerHand);
        printf("-----------------------------------------------------------------\n");
        break;
    
    case REVEAL :
        printf("Les enchères sont terminées, les cartes du dealer sont revélées \n");
        printf("\n");
        printf("-----------------------| MAIN DU DEALER |------------------------\n");
        printHand(&dealerHand);
        printf("--------------------------| PLATEAU |----------------------------\n");
        printBoard(board, 5, 0);
        printf("-------------------------| VOTRE MAIN |--------------------------\n");
        printHand(&playerHand);
        printf("-----------------------------------------------------------------\n");
        break;
    
    default:
        break;
    }

}


float playerBet(Bets *playerBoard, const Stage stage ) // Fonction qui se repète trop. Il faut changer la manière de faire + rajouter la possibilité de miser à convenance sur la case bonus
{
    int input;
    int inputBet;

    switch (stage)
    {
        case PREFLOP : 
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 3x ou 4x la mise de base.\n");
            printf("|| 0 pour ne pas jouer || 1 pour jouer 3x votre mise soit %d || 2 pour jouer 4x votre mise soit %d || 3 pour miser sur bonus || \n", 3*playerBoard->bet, 4*playerBoard->bet);
            scanf("%d", &input);
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
                case 3 :
                    printf("Entrez la valeur que vous voulez miser\n");
                    scanf(" %d", &inputBet);
                    //il faut rajouter une fonction qui fait un contôle de saisie
                    playerBoard->bonus = inputBet;
                    playerBoard->hasBonusBet = 1;
                    return inputBet;
                    break;

                default :
                    break;
            }
            break;

        case FLOP :
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 2x la mise de base\n");
            printf("|| 0 pour ne pas miser || ");
            if (playerBoard->hasBet == 0) {
                printf("1 pour jouer 2x votre mise soit %d || ", 2 * playerBoard->bet);
            }
            if (playerBoard->hasBonusBet == 0) {
                printf("2 pour miser sur bonus ||\n");
            }
            scanf("%d", &input);
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
                        printf("vous avez joué %d \n", playerBoard->play);
                        return 2*playerBoard->bet;
                        break;
                    }
                    else
                    {
                        printf("Option invalide.\n");
                        return 0;
                        break;
                    } 
                case 2 :
                    if( playerBoard->hasBonusBet == 0)
                    {
                        printf("Entrez la valeur que vous voulez miser\n");
                        scanf(" %d", &inputBet);
                        //il faut rajouter une fonction qui fait un contôle de saisie
                        playerBoard->bonus = inputBet;
                        playerBoard->hasBonusBet = 1;
                        return inputBet;
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
            printf("Mise mini de 1x la mise de base\n");
            printf("|| 0 pour ne pas miser || ");
            if (playerBoard->hasBet == 0) {
                printf("1 pour jouer 1x votre mise soit %d || ", playerBoard->bet);
            }
            if (playerBoard->hasBonusBet == 0) {
                printf("2 pour miser sur bonus ||\n");
            }
            scanf("%d", &input);
            switch (input)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    return 0;
                    break;
                case 1 :
                    if( playerBoard->hasBet == 0)
                    {
                        playerBoard->play =  playerBoard->bet;
                        playerBoard->hasBet = 1;
                        printf("vous avez joué %d \n", playerBoard->play);
                        return 2*playerBoard->bet;
                        break;
                    }
                    else
                    {
                        printf("Option invalide.\n");
                        return 0;
                        break;
                    } 
                case 2 :
                    if( playerBoard->hasBonusBet == 0)
                    {
                        printf("Entrez la valeur que vous voulez miser\n");
                        scanf(" %d", &inputBet);
                        //il faut rajouter une fonction qui fait un contôle de saisie
                        playerBoard->bonus = inputBet;
                        playerBoard->hasBonusBet = 1;
                        return inputBet;
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
        
        default :
            printf("erreur lors de l'appel de la fonction playerBet\n");
            break;
    }
}

float gamePayout(const int playerHandValue, const int dealerHandValue, const Bets playerBoard)
{
    int payout = 0;

    HandPayout payouts[] = {
        {501, 51}, // rang 0
        {51, 41}, //rang 1
        {11, 31}, //rang 2
        {4, 9}, //rang 3
        {3.5, 8},    //rang 4
        {2, 5},   //rang 5
        {0, 4}, //rang 6
        {0, 0}, //rang 7
        {0, 0}, //rang 8
        {0, 0} //rang 9
    };

    //printf("la première ligne de payout = rang %d multiplicateur mise = %d et bonus = %d \n", payouts[0].blindMultiplier, payouts[0].bonusMultiplier);

    int playerHandRank = hand_rank(playerHandValue);
    int dealerHandRank = hand_rank(dealerHandValue);

    printRank(playerHandRank, PLAYER);
    printRank(dealerHandRank, DEALER);

    if (playerHandRank < dealerHandRank) {
            printf("Le joueur gagne !\n");
            return payout = 2*(playerBoard.bet + playerBoard.play) + playerBoard.blind*payouts[playerHandRank].blindMultiplier + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
        } else if (playerHandRank > dealerHandRank) {
            printf("Le dealer gagne !\n");
            return payout = 0 + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
        } else {
            if (playerHandValue > dealerHandValue)
            {
                printf("le dealer gagne a la hauteur !\n");
                return payout = 0 + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
            else if (playerHandValue < dealerHandValue)
            {
                printf("le joueur gagne a la hauteur !\n");
                return payout = 2*(playerBoard.bet + playerBoard.play) + playerBoard.blind*payouts[playerHandRank].blindMultiplier + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
            else
            {
                printf("Le dealer et le joueur on la meme main !\n");
                return payout = playerBoard.bet + playerBoard.play + playerBoard.blind + playerBoard.bonus*payouts[playerHandRank].bonusMultiplier;
            }
        }
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
        printf("%s un Brelan\n", owner);
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

float poker_game(float playerCredits)
{
    int pokerGame = POKER_ON;

    Card deck[DECK_SIZE];
    PokerHand playerHand;
    PokerHand dealerHand;
    Card board[5];

    Bets playerBoard;

    initDeck(deck);

    while(pokerGame == POKER_ON)
    {
        playerBoard.blind = 0;
        playerBoard.bet = 0;
        playerBoard.play = 0;
        playerBoard.bonus = 0;
        playerBoard.hasBet = 0;
        playerBoard.hasBonusBet = 0;

        refreshDisplay();

        printf("Entrez la valeur de votre mise :\n");
        scanf("%d",&playerBoard.bet);
        playerBoard.blind = playerBoard.bet;
        playerCredits -= 2*playerBoard.bet;
        printf("vous avez misé %d, la blinde suit.\n", playerBoard.bet); // faire le contrôle de saisie

        Stage stage = PREFLOP;

        shuffleDeck(deck); // mélanger le paquet
        dealHand(deck, &playerHand); // distribuer une main
        dealHand(deck, &dealerHand); 
        dealBoard(deck, board, 5);
        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        playerCredits -= playerBet(&playerBoard, stage);

        stage = FLOP;

        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        playerCredits -= playerBet(&playerBoard, stage);
        
        stage = TURNRIVER;

        displayGame(stage, playerHand, playerBoard, dealerHand, board);
        playerCredits -= playerBet(&playerBoard, stage);
        
        stage = REVEAL;
        
        displayGame(stage, playerHand, playerBoard, dealerHand, board);

        Card playerSevenCardHand[7];
        Card dealerSevenCardHand[7];

        // On copie les deux cartes du joueur et les cinq cartes du board dans le tableau de sept cartes
        memcpy(playerSevenCardHand, playerHand.cards, sizeof(Card) * 2);
        memcpy(&playerSevenCardHand[2], board, sizeof(Card) * 5);

        // On copie les deux cartes du dealer et les cinq cartes du board dans le tableau de sept cartes
        memcpy(dealerSevenCardHand, dealerHand.cards, sizeof(Card) * 2);
        memcpy(&dealerSevenCardHand[2], board, sizeof(Card) * 5);

        playerCredits += gamePayout(eval_7hand(playerSevenCardHand), eval_7hand(dealerSevenCardHand), playerBoard);
        printf("Vous avez désormais %2.f $\n",playerCredits);
        
        printf("Voulez-vous rejouer ?\n(o/n)\n");
        char choixPoker;
        scanf(" %c",&choixPoker);

        switch (choixPoker)
        {
        case 'o':
            break;
        case 'n':
            pokerGame = POKER_OFF;
            return playerCredits;
            break;
        
        default:
            pokerGame = POKER_OFF;
            return playerCredits;
            break;
        }
    }
    
}
