#ifndef CASINO_H
#define CASINO_H

typedef struct {
    char name[50];
    float credits;
} Player;

void initialize_casino(void);
int lobby(void);
void shutdown_casino(void);

#endif //CASINO_H