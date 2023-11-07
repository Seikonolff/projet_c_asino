#include "poker.h"
#include "arrays.h"
#include <stdlib.h>
#include <stdio.h>

#define CLUBS    0x8000
#define DIAMONDS 0x4000
#define HEARTS   0x2000
#define SPADES   0x1000

#define	STRAIGHT_FLUSH  1
#define	FOUR_OF_A_KIND  2
#define	FULL_HOUSE      3
#define	FLUSH           4
#define	STRAIGHT        5
#define	THREE_OF_A_KIND 6
#define	TWO_PAIR        7
#define	ONE_PAIR        8
#define	HIGH_CARD       9

const int prime_numbers[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

// Attribuer à chaque carte un iddentifiant unique codé sur 32 bit 
int getCardIdentifier(int rank, int suit) {
    int card = 0;
    switch (suit)
    {
    case 0 :
        suit = HEARTS;
        break;
    case 1 :
        suit = SPADES;
        break;
    case 2 :
        suit = DIAMONDS;
        break;
    case 3 :
        suit = CLUBS;
        break;
    
    default:
        break;
    }

    // Les bits pour le rang spécifique (un seul bit défini parmi les 13 premiers bits)
    card |= 1 << (rank + 16); // Le décalage de 16 pour les 2 octets du milieu

    card |= suit;

    // Les bits pour le rang numérique
    card |= rank << 8; // Le décalage de 8 pour l'octet le plus à gauche

    // Les bits pour le nombre premier associé au rang de la carte
    card |= prime_numbers[rank];

    return card;
}

int hand_rank(unsigned short val)
{
    if (val > 6185) return HIGH_CARD;        // 1277 high card
    if (val > 3325) return ONE_PAIR;         // 2860 one pair
    if (val > 2467) return TWO_PAIR;         //  858 two pair
    if (val > 1609) return THREE_OF_A_KIND;  //  858 three-kind
    if (val > 1599) return STRAIGHT;         //   10 straights
    if (val > 322)  return FLUSH;            // 1277 flushes
    if (val > 166)  return FULL_HOUSE;       //  156 full house
    if (val > 10)   return FOUR_OF_A_KIND;   //  156 four-kind
    return STRAIGHT_FLUSH;                   //   10 straight-flushes
}

static unsigned find_fast(unsigned u)
{
    unsigned a, b, r;

    u += 0xe91aaa35;
    u ^= u >> 16;
    u += u << 8;
    u ^= u >> 4;
    b  = (u >> 8) & 0x1ff;
    a  = (u + (u << 2)) >> 19;
    r  = a ^ hash_adjust[b];
    return r;
}

static unsigned short eval_5cards(const Card *c1, const Card *c2, const Card *c3, const Card *c4, const Card *c5) {
    int q = (c1->id | c2->id | c3->id | c4->id | c5->id) >> 16;
    short s;

    // This checks for Flushes and Straight Flushes
    if (c1->id & c2->id & c3->id & c4->id & c5->id & 0xF000)
        return flushes[q];

    // This checks for Straights and High Card hands
    if ((s = unique5[q]))
        return s;

    // This performs a perfect-hash lookup for remaining hands
    q = (c1->id & 0xFF) * (c2->id & 0xFF) * (c3->id & 0xFF) * (c4->id & 0xFF) * (c5->id & 0xFF);
    return hash_values[find_fast(q)];
}

unsigned short eval_5hand(const Card *hand) {
    return eval_5cards(&hand[0], &hand[1], &hand[2], &hand[3], &hand[4]);
}

unsigned short eval_7hand(const Card *hand) {
    int i, j;
    Card subhand[5];
    unsigned short q, best = 9999;

    for (i = 0; i < 21; i++) {
        for (j = 0; j < 5; j++)
            subhand[j] = hand[perm7[i][j]];
        q = eval_5hand(subhand);
        if (q < best)
            best = q;
    }
    return best;
}