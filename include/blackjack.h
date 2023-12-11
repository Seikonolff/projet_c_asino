#ifndef BLACKJACK_H
#define BLACKJACK_H

float blackjack_game(float playerStack);
//int tirerCarte(int tot);
typedef struct {
    int valeur;  // Valeur de la carte (1 à 11 pour As à Roi)
    const char *nom;  // Nom de la carte (ex: "As", "Deux", ..., "Roi")
    const char *couleur;  // Couleur de la carte (ex: "Coeur", "Carreau", "Trèfle", "Pique")
} Carte;
void initialiserCartes(Carte jeu[]);
void melangerCartes(Carte jeu[]);
Carte tirerCarte(Carte jeu[], int *indice);
int croupier(int cartebanque, Carte HandC[], Carte jeu[], int *indicecarte);
int tourjoueur(int cartejoueur, int stackjoueur, float parijoueur, float *ptr, Carte jeu[], int *indicecarte, Carte mainjoueur[]);
float gagnant(int total, int banque, float stack_update, float player_bet);
float rejouer(float newstack);
void assurance(float pari, float stack, Carte Maincroup[], int totjou, Carte jeu[], int *indicecarte, Carte mainjou[]);
float mise();
void Hand(Carte Hand[],int compteur);
void printColor(const char *value, const char *suit, int type);
#endif //BLACKJACK_H
