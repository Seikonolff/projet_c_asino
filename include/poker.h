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
    DEALER,
} HandType;

typedef struct {
    int value; // value of the card, e.g., 2 for Two, 11 for Jack, etc.
    int suit;  // suit of the card, e.g., 0 for Hearts, 1 for Spades, etc.
    int id;
} Card;

typedef struct {
    int bet;
    int blind;
    int play;
    int bonus;
    int hasBet; // 1 pour TRUE 0 pour FALSE
    int hasFolded; // 1 pour TRUE 0 pour FALSE
} Bets;

void printCardTemp(const Card *card);
void initDeck(Card *deck);
void shuffleDeck(Card *deck);
void dealHands(Card *deck, Card *playerHand, Card *dealerHand);
void dealBoard(Card *deck, Card *board);
void printCards(const Card *board, int numCards, int hidden);
void printHiddenCard(int numCards);
void printStack(float stack_a_afficher);
void refreshDisplay(void);
void printBettingBoard(const Bets *bets);
void printRank(int rank, HandType type);
void printWelcome(void);
void printColored(const char *value, const char *suit, int type);
void displayGame(const Stage state, const Card *playerHand, const Bets playerBoard, const Card *dealerHand, const Card *board);
float playerBet(Bets *playerBoard, const float playerStack, const Stage stage );
float gamePayout(const int playerHandValue, const int dealerHandValue, const Bets playerBoard);
float poker_game(float playerCredits);
void sortHand(Card *hand, int size);

void printDeck(Card deck[], int size);

#endif // POKER_H
