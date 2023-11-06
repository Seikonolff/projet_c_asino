#include "blackjack.h"
#include "casino.h"
#include<stdio.h>
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()

#define MAX_JOUEURS 4


// Fonction pour tirer une carte aléatoire entre 1 et 11 (as vaut 11 par défaut).
int tirerCarte() {
    return rand() % 11 + 1;
}


void blackjack_game() {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    int totalJoueurs[MAX_JOUEURS] = {0};
    int totalCroupier = 0;
    int nombreJoueurs;
    int joueurstack = 1000;
    int kdo;
    int mise;

    printf("Entrez le nombre de joueurs (1-%d) : ", MAX_JOUEURS);
    scanf("%d", &nombreJoueurs);

    if (nombreJoueurs < 1 || nombreJoueurs > MAX_JOUEURS) {
        printf("Nombre de joueurs non valide.\n");
        return;
    }
    printf("Quel est votre mise ?");
    scanf("%d", &mise);

    int cartesJoueurs[MAX_JOUEURS][2] = {0};  // Tableau pour stocker les cartes des joueurs.

    // Distribution des cartes initiales pour chaque joueur et le croupier.
    for (int i = 0; i < nombreJoueurs; i++) {
        cartesJoueurs[i][0] = tirerCarte();
        cartesJoueurs[i][1] = tirerCarte();
        totalJoueurs[i] = cartesJoueurs[i][0] + cartesJoueurs[i][1];
    }

    totalCroupier += tirerCarte();
    printf("Main du croupier: %d\n", totalCroupier);

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Première carte du joueur %d : %d\n", i + 1, cartesJoueurs[i][0]);
    }

    totalCroupier += tirerCarte();

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Deuxième carte du joueur %d : %d\n", i + 1, cartesJoueurs[i][1]);
    }

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Main du joueur %d : %d\n", i + 1, totalJoueurs[i]);
    }

    // Tours des joueurs.
    for (int i = 0; i < nombreJoueurs; i++) {
        if (cartesJoueurs[i][0] == cartesJoueurs[i][1]) {
        char choix;
        printf("Joueur %d, vous avez deux cartes identiques. Voulez-vous doubler votre mise ? (o/n) : ", i + 1);
        scanf(" %c", &choix);
            
        if (choix == 'o') {
            mise *= 2;  // Doublez la mise.
            joueurstack -= mise;  // Retirez le montant de la mise du stack.
            printf("Vous avez doublé votre mise. Votre mise est maintenant de : %d\n", mise);
            }
            int jeu1 = totalJoueurs[i]/2;
            int jeu2 = totalJoueurs[i]/2;
            jeu1 += tirerCarte();
            jeu2 += tirerCarte();

            printf("Votre premier jeu est : %d\n", jeu1);
            printf("Votre deuxième jeu est : %d\n", jeu2);
        }

        while (totalJoueurs[i] < 21) {
            char choix;
            printf("Joueur %d, voulez-vous tirer une carte de plus ? (o/n) : ", i + 1);
            scanf(" %c", &choix);

            if (choix == 'o') {
                int nouvelleCarte = tirerCarte();
                printf("Joueur %d, vous avez tiré : %d\n", i + 1, nouvelleCarte);
                totalJoueurs[i] += nouvelleCarte;
                printf("Main du joueur %d : %d\n", i + 1, totalJoueurs[i]);
            } else {
                break;
            }
        }
    }
    printf("Main du croupier : %d\n\n", totalCroupier);
    
    // Tour du croupier.
    while (totalCroupier < 17) {
        int nouvelleCarte = tirerCarte();
        printf("Le croupier a tiré : %d\n", nouvelleCarte);
        totalCroupier += nouvelleCarte;
        printf("Main du croupier : %d\n", totalCroupier);
    }

    // Détermination des gagnants.
    for (int i = 0; i < nombreJoueurs; i++) {
        if (totalJoueurs[i] > 21) {
            printf("Joueur %d a dépassé 21. Le croupier gagne.\n", i + 1);
        } else if (totalCroupier > 21 || totalJoueurs[i] > totalCroupier) {
            printf("Joueur %d gagne !\n", i + 1);
            kdo = mise*2;
            joueurstack += kdo;
            printf("Votre stack est maintenant de: %d\n",joueurstack);
        } else if (totalCroupier > totalJoueurs[i]) {
            printf("Le croupier gagne contre joueur %d.\n", i + 1);
        } else {
            printf("Égalité entre joueur %d et le croupier !\n", i + 1);
        }
    }

}
