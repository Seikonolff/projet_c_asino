#include <stdio.h>
#include "casino.h"
#include "windows.h"

int main() {

    int gameRunning = 1;
    SetConsoleOutputCP(65001);
    initialize_casino();
    while (gameRunning)
        gameRunning = lobby();
        
    return 0;
}
