#include "poker.h"
//#include "pokerhandranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52

int currentCardIndex = 0;


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

// fonction pour évaluer une main - très simplifiée
int evaluateHand(PokerHand *hand) {
    // Ici, vous évaluerez la main selon les règles du poker et retournerez un score ou une évaluation.
    // Cette fonction nécessitera une logique complexe pour évaluer correctement toutes les combinaisons de poker.
    // Pour l'instant, nous retournons un placeholder.
    return 0; // placeholder
}

// fonction pour imprimer une carte
void printCard(const Card *card) {
    const char *suits[4] = {"Coeurs", "Piques", "Carreaux", "Trefles"};
    const char *values[13] = {"Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf", "Dix", "Valet", "Dame", "Roi", "As"};
    printf("%s de %s\n", values[card->value], suits[card->suit]);
}

// fonction pour imprimer une main
void printHand(const PokerHand *hand) {
    for(int i = 0; i < 2; i++) {
        printCard(&hand->cards[i]);
    }
}

void printBoard(const Card *board, int numCards) {
    for (int i = 0; i < numCards; i++) {
        printCard(&board[i]);
    }
}

void playerBet(Bets *playerBoard, const Stage stage )
{
    int temp;
    //printf("TEMP A POUR VALEUR : %d \n", temp);
    switch (stage)
    {
        case PREFLOP : 
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 3x ou 4x la mise de base.\n");
            printf("0 pour ne pas jouer || 1 pour jouer 3x votre mise soit %d || 2 pour jouer 4x votre mise soit %d\n", 3*playerBoard->bet, 4*playerBoard->bet);
            scanf("%d", &temp);
            switch (temp)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    playerBoard->play = 0;
                    break;
                case 1 :
                    playerBoard->play =  3*playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
                    break;
                case 2 :
                    playerBoard->play =  4*playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
                    break;
                default :
                    break;
            }
            break;

        case FLOP :
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 2x la mise de base.\n");
            printf("0 pour ne pas miser || 1 pour jouer 2x votre mise soit %d\n", 2*playerBoard->bet);
            scanf("%d", &temp);
            switch (temp)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    playerBoard->play = 0;
                    break;
                case 1 :
                    playerBoard->play =  2*playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
                    break;
                default :
                    break;
            }
            break;
        
        case TURNRIVER :
            printf("Voulez-vous jouer ?\n");
            printf("Mise mini de 2x la mise de base.\n");
            printf("0 pour ne pas miser || 1 pour jouer 1x votre mise soit %d\n", playerBoard->bet);
            scanf("%d", &temp);
            switch (temp)
            {
                case 0 :
                    printf("vous ne jouez pas.\n");
                    playerBoard->play = 0;
                    break;
                case 1 :
                    playerBoard->play =  playerBoard->bet;
                    printf("vous avez joue %d \n", playerBoard->play);
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

/*FinalPokerHand evaluateBestHand(Card *holeCards, Card *communityCards) {
    PokerHand bestHand;
    bestHand.ranking = HIGH_CARD; // La plus faible combinaison possible

    Card possibleHand[7];

    // Copier les deux cartes du joueur et les cinq cartes du board dans possibleHand
    memcpy(possibleHand, holeCards, 2 * sizeof(Card));
    memcpy(possibleHand + 2, communityCards, 5 * sizeof(Card));

    // Trier possibleHand pour faciliter la vérification des combinaisons
    qsort(possibleHand, 7, sizeof(Card), compareCards);

    // Générer toutes les combinaisons de 5 cartes à partir des 7 cartes disponibles
    // et trouver la meilleure combinaison.
    Card tempHand[5];
    for (int i = 0; i < 21; ++i) { // Il y a 21 combinaisons différentes pour choisir 5 cartes parmi 7
        for (int j = 0, k = 0; j < 7; ++j) {
            if (!(i & (1 << j))) { // Utiliser un masque pour inclure ou exclure chaque carte
                tempHand[k++] = possibleHand[j];
                if (k == 5) { // Quand nous avons sélectionné 5 cartes
                    PokerHand currentHand;
                    memcpy(currentHand.cards, tempHand, 5 * sizeof(Card));
                    currentHand.ranking = evaluateHand(tempHand);
                    if (currentHand.ranking > bestHand.ranking) {
                        bestHand = currentHand;
                    }
                    break;
                }
            }
        }
    }
    // bestHand contient maintenant la meilleure main de poker de 5 cartes du joueur
    // bestHand.ranking est le classement de cette main
    return bestHand;
}*/

void poker_game()
{
    Stage stage = PREFLOP;
    Card deck[DECK_SIZE];
    PokerHand playerHand;
    PokerHand dealerHand;
    Card board[5];

    Bets playerBoard;

    // initialiser le paquet (ceci est une simplification)
    for(int i = 0; i < 4; i++) { // pour chaque couleur
        for(int j = 0; j < 13; j++) { // pour chaque rang
            deck[i * 13 + j].suit = i;
            deck[i * 13 + j].value = j;
        }
    }

    printf("Entrez la valeur de votre mise :\n");
    scanf("%d",&playerBoard.bet);
    playerBoard.blind = playerBoard.bet;
    //playerBoard.play = 0;

    printf("vous avez mise %d, la blinde suit.\n", playerBoard.bet); // faire le contrôle de saisie

    shuffleDeck(deck); // mélanger le paquet
    dealHand(deck, &playerHand); // distribuer une main
    dealHand(deck, &dealerHand);
    dealBoard(deck, board, 3); // Deal flop

    printf("Votre main est :\n");
    printHand(&playerHand);

    playerBet(&playerBoard, stage);

    stage = FLOP;

    printf("1er tour enchere passe, le flop est revele \n");
    printf("FLOP : \n");
    printBoard(board, 3); // For the flop

    

    if (playerBoard.play == 0)
        playerBet(&playerBoard, stage);
    
    stage = TURNRIVER;

    printf("2nd tour des enchere passe, la turn et river sont reveles\n");
    printf("BOARD : \n");
    dealBoard(deck, board + 3, 1); // Deal 1 card for the turn
    dealBoard(deck, board + 4, 1); // Deal 1 card for the river
    printBoard(board, 5); // For the flop, turn, and river
    
    if (playerBoard.play == 0)
        playerBet(&playerBoard, stage);
    
    printf("Les encheres sont cloturees, les cartes du dealer sont revelees\n");
    printHand(&dealerHand);

    printf("mise = %d , blinde = %d et play = %d \n",playerBoard.bet, playerBoard.blind, playerBoard.play);
    printf("et la on evalue bisous\n");

    //il reste à developper un algo type Cactus Kev's


    return;
}
