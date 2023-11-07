#include <stdio.h>
#include "casino.h"

int main() {

    int gameRunning = 1;
    initialize_casino();
    while (gameRunning)
        gameRunning = lobby();
        
    return 0;
}
