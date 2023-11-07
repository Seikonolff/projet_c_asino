#ifndef POKER_H
#define POKER_H

typedef enum {
    PREFLOP,
    FLOP,
    TURNRIVER,
} Stage;

typedef struct {
    int value; // value of the card, e.g., 2 for Two, 11 for Jack, etc.
    int suit;  // suit of the card, e.g., 0 for Hearts, 1 for Spades, etc.
} Card;

typedef struct {
    Card cards[2];  // a poker hand contains 2 cards
} PokerHand;

/*typedef struct {
    Card cards[5];
    HandRanking ranking;
} FinalPokerHand;*/

typedef struct {
    int bet;
    int blind;
    int play;
} Bets;

void shuffleDeck(Card *deck);
void dealHand(Card *deck, PokerHand *hand);
void dealBoard(Card *deck, Card *board, int numCards);
int evaluateHand(PokerHand *hand);
void printCard(const Card *card);
void printHand(const PokerHand *hand);
void printBoard(const Card *board, int numCards);
void playerBet(Bets *playerHand, const Stage stage);
//PokerHand evaluateBestHand(Card *holeCards, Card *communityCards);
void poker_game(void);

#endif // POKER_H
