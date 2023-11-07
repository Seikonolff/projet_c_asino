#ifndef POKERHANDRANKING_H
#define POKERHANDRANKING_H

typedef enum {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
} HandRanking;

int getCardIdentifier(int rank, int suit);
//int makeCard(int rank, char suit);
//int makeCard2(int rank, char suit);


#endif // POKERHANDRANKING_H