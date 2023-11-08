#include "blackjack.h"
#include "casino.h"
#include <stdio.h>
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()

#define MAX_JOUEURS 4


// Fonction pour tirer une carte aléatoire entre 1 et 11 (as vaut 11 par défaut).
int tirerCarte() {
    return rand() % 11 + 1;
}

void rejouer() {
    char jouer;
    printf("Voulez-vous rejouer ? (o/n)\n");
    scanf(" %c",&jouer);
    if (jouer == 'o') {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    blackjack_game();
    }
}

void gagnant(int total, int banque) {
    if (total > 21) {
        printf("Vous avez dépassé 21. Le croupier gagne.\n");
    } else if (banque > 21 || total > banque) {
        printf("Vous avez gagné !\n");
        //kdo = mise*2;
        //joueurstack += kdo;
        //printf("Votre stack est maintenant de: %f\n",joueurstack);
    } else if (banque > total) {
        printf("Le croupier gagne dommage...\n");
    } else {
        printf("Égalité entre vous et le croupier !\n");
    }
}

int tourjoueur(int cartejoueur) {
    if (cartejoueur == 0) {
        return cartejoueur;
    }
    else {
    while (cartejoueur < 21) {
        char choix;
        printf("Voulez-vous tirer une carte de plus ou doubler ? (o/n/d) : ");
        scanf(" %c", &choix);

        if (choix == 'o') {
            int nouvelleCarte = tirerCarte();
            printf("Vous avez tiré : %d\n", nouvelleCarte);
            cartejoueur += nouvelleCarte;
            printf("Votre main : %d\n", cartejoueur);
        } else if (choix == 'd'){
            int nouvelleCarte = tirerCarte();
            printf("Vous avez tiré : %d\n", nouvelleCarte);
            cartejoueur += nouvelleCarte;
            printf("Votre main : %d\n", cartejoueur);
            break;
        }
        else {
            break;
        }
    }
    }
    return cartejoueur;
}

int croupier(int cartebanque) {
    while (cartebanque < 17) {
        int nouvelleCarte = tirerCarte();
        printf("Le croupier a tiré : %d\n", nouvelleCarte);
        cartebanque += nouvelleCarte;
        printf("Main du croupier : %d\n", cartebanque);
    }
    return cartebanque;
}


void blackjack_game() {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    int totalJoueurs[MAX_JOUEURS] = {0};
    int totalCroupier = 0;
    int nombreJoueurs;
    float joueurstack = 1000;
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
        if (totalJoueurs[i] == 21)
        {
            printf("Main du joueur %d : %d\n", i+1, totalJoueurs[i]);
            printf("Bravo joueur %d vous avez un BlackJack !\n", i+1);
            joueurstack += mise*2.5;
            printf("Votre nouveau stack est: %f\n",joueurstack);
            totalJoueurs[i] = 0;
        }
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
        printf("Joueur %d, vous avez deux cartes identiques. Voulez-vous split votre jeu en doublant votre mise ? (o/n) : ", i + 1);
        scanf(" %c", &choix);
            
            if (choix == 'o') {
                mise *= 2;  // Doublez la mise.
                joueurstack -= mise;  // Retirez le montant de la mise du stack.
                printf("Vous avez split votre jeu. Votre mise est maintenant de : %d\n", mise);
                
                int jeu1 = totalJoueurs[i]/2;
                int jeu2 = totalJoueurs[i]/2;
                jeu1 += tirerCarte();
                jeu2 += tirerCarte();

                printf("Votre premier jeu est : %d\n", jeu1);
                printf("Votre deuxième jeu est : %d\n", jeu2);
                
                //Blackjack avec deux jeux
                jeu1 = tourjoueur(jeu1);
                jeu2 = tourjoueur(jeu2);
                
        
                printf("Main du croupier : %d\n\n", totalCroupier);
            
                // Tour du croupier.
                totalCroupier = croupier(totalCroupier);

                // Détermination des gagnants.
                    gagnant(jeu1,totalCroupier);
                    gagnant(jeu2,totalCroupier);
                    rejouer();

            }
            else {  //Cas carte identiques mais ne souhaite pas split
                totalJoueurs[i] = tourjoueur(totalJoueurs[i]);

            printf("Main du croupier : %d\n\n", totalCroupier);
        
            // Tour du croupier.
            totalCroupier = croupier(totalCroupier);

            // Détermination des gagnants.
            gagnant(totalJoueurs[i], totalCroupier);
            rejouer();
            }
        }
        else { //Cas classique du blackjack
        totalJoueurs[i] = tourjoueur(totalJoueurs[i]);

        printf("Main du croupier : %d\n\n", totalCroupier);
    
        // Tour du croupier.
        totalCroupier = croupier(totalCroupier);

        // Détermination des gagnants.
        gagnant(totalJoueurs[i], totalCroupier);
        rejouer();
        }
    }
}