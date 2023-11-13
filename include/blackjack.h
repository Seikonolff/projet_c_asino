#ifndef BLACKJACK_H
#define BLACKJACK_H

float blackjack_game(float playerStack);
int tirerCarte(int tot);
int croupier(int cartebanque, int HandC[]);
int tourjoueur(int cartejoueur, int stackjoueur, float parijoueur, float *ptr);
float gagnant(int total, int banque, float stack_update, float player_bet);
void rejouer(float newstack);
float mise();
void Hand(int Hand[], int compteur);

#endif //BLACKJACK_H
