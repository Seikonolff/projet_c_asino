#ifndef DATABASE_H
#define DATABASE_H


void update_player_credit(char *nom_joueur, float *stack_joueur);
int check_player_in_db(char *nom_joueur, float *stack_joueur);
void arrivee_joueur(char *nom_joueur, float *stack_joueur);

#endif