#ifndef CASINO_H
#define CASINO_H

typedef struct {
    //str name;
    float credits;
} Player;

void initialize_casino();
int lobby(void);
void shutdown_casino();

#endif //CASINO_H