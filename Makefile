all:
		gcc -o ../bin/casino_game main.c casino.c poker.c pokerhandranking.c blackjack.c slots.c roulette.c database.c -I../include -L../lib -lsqlite3