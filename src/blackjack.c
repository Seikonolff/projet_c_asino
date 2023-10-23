#include "blackjack.h"
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()

#define MAX_JOUEURS 4

// Fonction pour tirer une carte aléatoire entre 1 et 11 (as vaut 11 par défaut).
int tirerCarte() {
    return rand() % 11 + 1;
}

int main() {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    int totalJoueurs[MAX_JOUEURS] = {0};
    int totalCroupier = 0;
    int nombreJoueurs;

    printf("Entrez le nombre de joueurs (1-%d) : ", MAX_JOUEURS);
    scanf("%d", &nombreJoueurs);

    if (nombreJoueurs < 1 || nombreJoueurs > MAX_JOUEURS) {
        printf("Nombre de joueurs non valide.\n");
        return 1;
    }

    // Distribution des cartes initiales pour chaque joueur et le croupier.
    for (int i = 0; i < nombreJoueurs; i++) {
        totalJoueurs[i] += tirerCarte();
    }

    totalCroupier += tirerCarte();
    printf("Main du croupier: %d\n", totalCroupier);

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Main du joueur %d : %d\n", i + 1, totalJoueurs[i]);
    }
        for (int i = 0; i < nombreJoueurs; i++) {
        totalJoueurs[i] += tirerCarte();
    }

    totalCroupier += tirerCarte();

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Main du joueur %d : %d\n", i + 1, totalJoueurs[i]);
    }

    printf("Main du croupier : %d\n\n", totalCroupier);

    // Tours des joueurs.
    for (int i = 0; i < nombreJoueurs; i++) {
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
        } else if (totalCroupier > totalJoueurs[i]) {
            printf("Le croupier gagne contre joueur %d.\n", i + 1);
        } else {
            printf("Égalité entre joueur %d et le croupier !\n", i + 1);
        }
    }

    return 0;
}
