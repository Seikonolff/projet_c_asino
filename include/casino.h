#ifndef CASINO_H
#define CASINO_H

typedef enum {
    POKER,
    BLACKJACK,
    SLOTS,
    ROULETTE,
} GameType;

typedef struct {
    //str name;
    float credits;
} Player;

void initialize_casino();
int lobby(void);
void start_game(GameType game_type);
void update_player_credits(int amount);
void shutdown_casino();

#endif //CASINO_H