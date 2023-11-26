#ifndef ROULETTE_H
#define ROULETTE_H

float roulette_game(float credits);
int userbet(int balance);
int getBetType();
int getSpecificNumber();
int getColor(int betType);
int getTier();
void getChevalNumbers(int *num1, int *num2);
void getCarreNumbers(int *num1, int *num2, int *num3, int *num4);
int getColumn();
int getTwoColumns();
int getLine();
int getTwoLines();
int getNumberColor(int number);

#endif //ROULETTE_H