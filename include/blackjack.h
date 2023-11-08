#ifndef BLACKJACK_H
#define BLACKJACK_H

void blackjack_game(void);
int tirerCarte(void);
int croupier(int cartebanque);
int tourjoueur(int cartejoueur);
void gagnant(int total, int banque);
void rejouer(void);


#endif //BLACKJACK_H
