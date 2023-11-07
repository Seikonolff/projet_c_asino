#ifndef POKERHANDRANKING_H
#define POKERHANDRANKING_H

int getCardIdentifier(int rank, int suit);
int hand_rank(unsigned short val);
static unsigned find_fast(unsigned u);
static unsigned short eval_5cards(const Card *c1, const Card *c2, const Card *c3, const Card *c4, const Card *c5);
unsigned short eval_5hand(const Card *hand);
unsigned short eval_7hand(const Card *hand);

#endif // POKERHANDRANKING_H