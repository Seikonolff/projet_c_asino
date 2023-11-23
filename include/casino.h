#ifndef CASINO_H
#define CASINO_H

typedef struct {
    float credits;
} Player;

void initialize_casino();
int lobby(void);
void shutdown_casino();

#endif //CASINO_H