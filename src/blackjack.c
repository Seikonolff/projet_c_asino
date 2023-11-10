#include "blackjack.h"
#include "casino.h"
#include <stdio.h>
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()

#define MAX_JOUEURS 1
#define MISE_MINI 10

// Fonction pour tirer une carte aléatoire entre 1 et 11 (as vaut 11 par défaut).
int tirerCarte(int tot) {
    int carte;
    int combi;

    carte = rand() % 10 + 2;
    combi = tot + carte;

    if (carte == 11 && combi > 21) {
        return carte - 10;
    }
    else {
        return carte;
    }
}

void rejouer(float newstack) {
    char jouer;
    printf("Voulez-vous rejouer ? (o/n)\n");
    scanf(" %c",&jouer);
    if (jouer == 'o') {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    blackjack_game(newstack);
    }
}

float gagnant(int total, int banque, float stack_update, float player_bet) {
    if (total > 21) {
        printf("Vous avez dépassé 21. Le croupier gagne.\n");
        stack_update -= player_bet;
        printf("Votre stack est maintenant de : %f\n", stack_update);
        return stack_update;
    } else if (banque > 21 || total > banque) {
        printf("Vous avez gagné !\n");
        float gain = player_bet*2;
        stack_update += gain;
        printf("Votre stack est maintenant de : %f\n",stack_update);
        return stack_update;
    } else if (banque > total) {
        printf("Le croupier gagne dommage...\n");
        stack_update -= player_bet;
        printf("Votre stack est maintenant de : %f\n",stack_update);
        return stack_update;
    } else {
        printf("Égalité entre vous et le croupier !\n");
        return stack_update;
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
            int nouvelleCarte = tirerCarte(cartejoueur);
            printf("Vous avez tiré : %d\n", nouvelleCarte);
            cartejoueur += nouvelleCarte;
            printf("Votre main : %d\n", cartejoueur);
        } else if (choix == 'd'){
            int nouvelleCarte = tirerCarte(cartejoueur);
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
        int nouvelleCarte = tirerCarte(cartebanque);
        printf("Le croupier a tiré : %d\n", nouvelleCarte);
        cartebanque += nouvelleCarte;
        printf("Main du croupier : %d\n", cartebanque);
    }
    return cartebanque;
}

float mise() {
    float bet;
    printf("Quel est votre mise ?");
    scanf(" %f", &bet);
    if (mise < MISE_MINI) {
        printf("La mise minimale est de 10$");
        return mise();
    }
    else {
        return bet;
    }
}



float blackjack_game(float playerStack) {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    int totalJoueurs[MAX_JOUEURS] = {0};
    int totalCroupier = 0;
    int nombreJoueurs;

    printf("Entrez le nombre de joueurs (1-%d) : ", MAX_JOUEURS);
    scanf("%d", &nombreJoueurs);

    if (nombreJoueurs < 1 || nombreJoueurs > MAX_JOUEURS) {
        printf("Nombre de joueurs non valide.\n");
        return playerStack;
    }

    if (playerStack < MISE_MINI) {
        printf("Vous n'avez pas assez d'argent veuillez aller à la banque si vous voulez jouer.");
        return playerStack;
    }

    float pari = mise();

    int cartesJoueurs[MAX_JOUEURS][2] = {0};  // Tableau pour stocker les cartes des joueurs.

    // Distribution des cartes initiales pour chaque joueur et le croupier.
    for (int i = 0; i < nombreJoueurs; i++) {
        cartesJoueurs[i][0] = tirerCarte(totalJoueurs[i]);
        cartesJoueurs[i][1] = tirerCarte(totalJoueurs[i]);
        totalJoueurs[i] = cartesJoueurs[i][0] + cartesJoueurs[i][1];
        if (totalJoueurs[i] == 21)
        {
            printf("Main du joueur %d : %d\n", i+1, totalJoueurs[i]);
            printf("Bravo joueur %d vous avez un BlackJack !\n", i+1);
            playerStack += pari*2.5;
            printf("Votre nouveau stack est: %f\n",playerStack);
            totalJoueurs[i] = 0;
        }
    }

    totalCroupier += tirerCarte(totalCroupier);
    printf("Main du croupier: %d\n", totalCroupier);

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Première carte du joueur %d : %d\n", i + 1, cartesJoueurs[i][0]);
    }

    totalCroupier += tirerCarte(totalCroupier);

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
                float doublage = pari*2;  // Doublez la mise.
                playerStack -= doublage;  // Retirez le montant de la mise du stack.
                printf("Vous avez split votre jeu. Votre mise est maintenant de : %d\n", doublage);
                
                int jeu1 = totalJoueurs[i]/2;
                int jeu2 = totalJoueurs[i]/2;
                jeu1 += tirerCarte(jeu1);
                jeu2 += tirerCarte(jeu2);

                printf("Votre premier jeu est : %d\n", jeu1);
                printf("Votre deuxième jeu est : %d\n", jeu2);
                
                //Blackjack avec deux jeux
                jeu1 = tourjoueur(jeu1);
                jeu2 = tourjoueur(jeu2);
                
        
                printf("Main du croupier : %d\n\n", totalCroupier);
            
                // Tour du croupier.
                totalCroupier = croupier(totalCroupier);

                // Détermination des gagnants.
                    float update1 = gagnant(jeu1,totalCroupier,playerStack,pari);
                    playerStack = update1;
                    float update2 = gagnant(jeu2,totalCroupier,playerStack,pari);
                    playerStack = update2;
                    rejouer(playerStack);

            }
            else {  //Cas carte identiques mais ne souhaite pas split
                totalJoueurs[i] = tourjoueur(totalJoueurs[i]);

            printf("Main du croupier : %d\n\n", totalCroupier);
        
            // Tour du croupier.
            totalCroupier = croupier(totalCroupier);

            // Détermination des gagnants.
            float update3 = gagnant(totalJoueurs[i], totalCroupier, playerStack, pari);
            playerStack = update3;
            rejouer(playerStack);
            }
        }
        else { //Cas classique du blackjack
        totalJoueurs[i] = tourjoueur(totalJoueurs[i]);

        printf("Main du croupier : %d\n\n", totalCroupier);
    
        // Tour du croupier.
        totalCroupier = croupier(totalCroupier);

        // Détermination des gagnants.
        float update4 = gagnant(totalJoueurs[i], totalCroupier, playerStack, pari);
        playerStack = update4;
        rejouer(playerStack);
        }
    }
return playerStack;
}