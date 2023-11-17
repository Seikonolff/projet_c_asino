#ifndef POKERHANDRANKING_H
#define POKERHANDRANKING_H


typedef struct {
    float blindMultiplier; // Multiplicateur pour la mise à la blinde
    float bonusMultiplier; // Multiplicateur pour le bonus
} HandPayout;

typedef enum {
    PLAYER_HAND,
    DEALER_HAND
} HandOwner;

int getCardIdentifier(int suit, int rank);
int hand_rank(unsigned short val);
static unsigned find_fast(unsigned u);
static unsigned short eval_5cards(const Card *c1, const Card *c2, const Card *c3, const Card *c4, const Card *c5);
unsigned short eval_5hand(const Card *hand);
unsigned short eval_7hand(const Card *hand, HandOwner type);
void printColoredCard(const char *value, const char *suit, int colorCode);
void printBestHand(const Card *board, int numCards);

#endif // POKERHANDRANKING_H