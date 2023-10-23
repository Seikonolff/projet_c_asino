#include <stdio.h>
#include "casino.h"

int main() {

    int gameRunning = 1;
    while (gameRunning)
        gameRunning = lobby();
        
    return 0;
}
