#ifndef SLOTS_H
#define SLOTS_H


typedef struct
{
int item; //item utilisé pour assigné un objet 
char nom_slot [50]; //nom de la machine
}
slot;

void init_rouleaux(void);
void init_aleatoire(void);
int tirage_slot(void);
char* affichage_item(int rouleau);
int check_results(void);
float gain(float mise, int resultat);
float slots_game(float stack);

#endif //SLOTS_H
