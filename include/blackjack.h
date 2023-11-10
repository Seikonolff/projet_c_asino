#ifndef BLACKJACK_H
#define BLACKJACK_H

float blackjack_game(float playerStack);
int tirerCarte(int tot);
int croupier(int cartebanque);
int tourjoueur(int cartejoueur);
float gagnant(int total, int banque, float stack_update, float player_bet);
void rejouer(float newstack);
float mise();


#endif //BLACKJACK_H
