#ifndef SLOTS_H
#define SLOTS_H


typedef struct
{
int item; //item utilisé pour assigné un objet 
char nom_slot [50]; //nom de la machine
}
slot;

void clear_terminal(void);
void affichage_stack(float stack_a_afficher);
float mise_joueur(void);
float mise_conforme(float bet_joueur, float stack_joueur);
float cas_conformite(int cas_conforme, float bet_joueur_2, float stack_joueur2);
void init_rouleaux(void);
void init_aleatoire(void);
int tirage_slot(void);
char* affichage_item(int rouleau);
int check_results(void);
void affichage_results(int resultat, float benefice);
float gain(float mise, int resultat);
float slots_game(float stack);

#endif //SLOTS_H
