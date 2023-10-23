#ifndef CASINO_H
#define CASINO_H

typedef enum {
    POKER,
    BLACKJACK,
    SLOTS,
} GameType;

typedef struct {
    int credits;
} Player;

void initialize_casino();
void start_game(GameType game_type);
void handle_game_logic();
void update_player_credits(int amount);
void shutdown_casino();

#endif //CASINO_H