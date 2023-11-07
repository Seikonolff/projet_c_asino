#include "poker.h"
#include "pokerhandranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int evaluateHand(PokerHand *hand) {
    return 0; // placeholder
}

// fonction pour imprimer une carte
void printCard(const Card *card) {
    const char *suits[4] = {"Coeurs", "Piques", "Carreaux", "Trefles"};
    const char *values[13] = {"Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf", "Dix", "Valet", "Dame", "Roi", "As"};
    printf("%s de %s\n", values[card->value], suits[card->suit]);
    //printf("id = %d \n", card->id);
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

float poker_game(float playerCredits)
{
    float newStack = 0;

    Stage stage = PREFLOP;

    Card deck[DECK_SIZE];
    PokerHand playerHand;
    PokerHand dealerHand;
    Card board[5];

    Bets playerBoard;

    // initialiser le paquet
    for(int i = 0; i < 4; i++) { // pour chaque couleur
        for(int j = 0; j < 13; j++) { // pour chaque rang
            deck[i * 13 + j].suit = i;
            deck[i * 13 + j].value = j;
            deck[i * 13 + j].id = getCardIdentifier(j , i);
            //printCard(&deck[i * 13 + j]);
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
    printf("---------------------------MAIN DU DEALER------------------------\n");
    printHand(&dealerHand);
    printf("---------------------------PLATEAU-------------------------------\n");
    printBoard(board, 5);
    printf("---------------------------VOTRE MAIN----------------------------\n");
    printHand(&playerHand);
    printf("-----------------------------------------------------------------\n");

    //printf("mise = %d , blinde = %d et play = %d \n",playerBoard.bet, playerBoard.blind, playerBoard.play);

    Card playerSevenCardHand[7];
    Card dealerSevenCardHand[7];

    // On copie les deux cartes du joueur et les cinq cartes du board dans le tableau de sept cartes
    memcpy(playerSevenCardHand, playerHand.cards, sizeof(Card) * 2);
    memcpy(&playerSevenCardHand[2], board, sizeof(Card) * 5);

    // On copie les deux cartes du dealer et les cinq cartes du board dans le tableau de sept cartes
    memcpy(dealerSevenCardHand, dealerHand.cards, sizeof(Card) * 2);
    memcpy(&dealerSevenCardHand[2], board, sizeof(Card) * 5);

    // On evalue les mains du joueur et du dealer
    unsigned short playerHandValue = eval_7hand(playerSevenCardHand);
    unsigned short dealerHandValue = eval_7hand(dealerSevenCardHand);

    // On obtient le classement des mains
    int playerHandRank = hand_rank(playerHandValue);
    int dealerHandRank = hand_rank(dealerHandValue);
    printf("la valeur de votre main est de %d \n",playerHandValue);
    printf("la valeur de la main du dealer est de %d \n",dealerHandValue);

    printf("La main du joueur est evaluee à : %d\n", playerHandRank);
    printf("La main du dealer est evaluee à : %d\n", dealerHandRank);

    // Comparez les mains pour déterminer le gagnant
    if (playerHandRank < dealerHandRank) {
        printf("Le joueur gagne !\n");
        newStack = playerCredits + playerBoard.bet; // ou une autre logique de paiement
    } else if (playerHandRank > dealerHandRank) {
        printf("Le dealer gagne !\n");
        newStack = playerCredits - playerBoard.bet; // ou une autre logique de paiement
    } else {
        if (playerHandValue > dealerHandValue)
        {
            printf("le dealer gagne a la hauteur !\n");
        }
        else if (playerHandValue < dealerHandValue)
        {
            printf("le joueur gagne a la hauteur !\n");
        }
        else
        {
            printf("Le dealer et le joueur on la meme main !\n");
        }
    }

    return newStack;
}
