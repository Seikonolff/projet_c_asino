//#include "pokerhandranking.h"
#include "poker.h"
#include "arrays.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define CLUBS    0x8000
#define DIAMONDS 0x4000
#define HEARTS   0x2000
#define SPADES   0x1000

#define ROYAL_FLUSH     0
#define	STRAIGHT_FLUSH  1
#define	FOUR_OF_A_KIND  2
#define	FULL_HOUSE      3
#define	FLUSH           4
#define	STRAIGHT        5
#define	THREE_OF_A_KIND 6
#define	TWO_PAIR        7
#define	ONE_PAIR        8
#define	HIGH_CARD       9

// Attribuer à chaque carte un iddentifiant unique codé sur 32 bit 
int getCardIdentifier(int suit, int rank) {
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
    card |= primes[rank];

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
    if (val == 1)   return ROYAL_FLUSH;      // 1 Royal Flush (most powerfull hand wow)
    return STRAIGHT_FLUSH;                   // 9 straight-flushes without Royal Flush
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

unsigned short eval_7hand(const Card *hand, HandType type) {
    int i, j;
    Card subhand[5];
    Card besthand[5];
    unsigned short q, best = 9999;

    for (i = 0; i < 21; i++) {
        for (j = 0; j < 5; j++)
            subhand[j] = hand[perm7[i][j]];
        q = eval_5hand(subhand);
        if (q < best)
        {
            best = q;
            for (j = 0; j < 5; j++)
                besthand[j] = subhand[j];
        }
    }
    if(type == PLAYER)
        printf("Main du joueur :\n");
    else
        printf("Main du croupier :\n");
    sortHand(besthand, sizeof(besthand) / sizeof(besthand[0]));
    printCards(besthand,5,0);

    return best;
}

void sortHand(Card *hand, int size) {
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (hand[j].value < hand[j + 1].value) {
                // Échange les cartes
                Card temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
                swapped = true;
            }
        }
        // Si aucun échange n'a été fait, le tableau est trié
        if (!swapped)
            break;
    }
}