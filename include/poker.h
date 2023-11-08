#ifndef POKER_H
#define POKER_H

#define POKER_ON 1
#define POKER_OFF 0

typedef enum {
    PREFLOP,
    FLOP,
    TURNRIVER,
    REVEAL,
} Stage;

typedef enum {
    PLAYER,
    DEALER
} HandType;

typedef struct {
    int value; // value of the card, e.g., 2 for Two, 11 for Jack, etc.
    int suit;  // suit of the card, e.g., 0 for Hearts, 1 for Spades, etc.
    int id;
} Card;

typedef struct {
    Card cards[2];  // a poker hand contains 2 cards
} PokerHand;

typedef struct {
    int bet;
    int blind;
    int play;
    int bonus;
    int hasBet; // 1 pour TRUE 0 pour FALSE
    int hasBonusBet;    // 1 pour TRUE 0 pour FALSE
} Bets;

void initDeck(Card *deck);
void shuffleDeck(Card *deck);
void dealHand(Card *deck, PokerHand *hand);
void dealBoard(Card *deck, Card *board, int numCards);
void printHand(const PokerHand *hand);
void refreshDisplay(void);
void displayGame(const Stage state, const PokerHand playerHand, const Bets playerBoard, const PokerHand dealerHand, const Card *board);
void printBoard(const Card *board, int numCards, int hidden);
float playerBet(Bets *playerHand, const Stage stage);
float gamePayout(const int playerHandValue, const int dealerHandValue, const Bets playerBoard);
void printRank(int rank, HandType type);
float poker_game(float playerCredits);

#endif // POKER_H
