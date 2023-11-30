#include "blackjack.h"
#include "casino.h"
#include <stdio.h>
#include <stdlib.h> // pour rand() et srand()
#include <time.h> // pour time()
#include <string.h>
#include <unistd.h> // pour sleep

#define MAX_JOUEURS 1
#define MISE_MINI 10

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define CYA  "\x1B[36m"
#define WHT  "\033[37m"

// Fonction pour tirer une carte aléatoire entre 2 et 11 (as vaut 11 par défaut).
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
    sleep(2);
    if (total > 21) {
        printf("Vous avez dépassé 21. Le croupier gagne.\n");
        stack_update -= player_bet;
        printf("Votre stack est maintenant de : %f\n", stack_update);
        return stack_update;
    } else if (banque > 21 || total > banque) {
        printf("Vous avez gagné !\n");
        float gain = player_bet;
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

int tourjoueur(int cartejoueur, int stackjoueur, float parijoueur, float *ptr) {
    if (cartejoueur == 0) {
        return cartejoueur;
    }
    else {
        while (cartejoueur < 21) {
            sleep(1);
            if (stackjoueur >= 2* parijoueur) { //Possibilité de doubler car stack suffisant
                char choix;
                printf("Voulez-vous tirer une carte de plus ou doubler ? (o/n/d) : ");
                scanf(" %c", &choix);


                if (choix == 'o') {
                    int nouvelleCarte = tirerCarte(cartejoueur);
                    printf("Vous avez tiré : %d\n", nouvelleCarte);
                    cartejoueur += nouvelleCarte;
                    Hand(&nouvelleCarte,1);
                    printf("Votre main : %d\n", cartejoueur);
                } else if (choix == 'd'){
                    int nouvelleCarte = tirerCarte(cartejoueur);
                    cartejoueur += nouvelleCarte;
                    *ptr += parijoueur;
                    printf("Votre mise est maintenant de : %f\n", *ptr);
                    printf("Vous avez tiré : %d\n", nouvelleCarte);
                    Hand(&nouvelleCarte,1);
                    printf("Votre main : %d\n", cartejoueur);
                    break;
                }
                else {
                    break;
                }
            }
            else { //Joueur ne peut pas doubler car il n'a pas le stak suffisant
                char choix;
                printf("Voulez-vous tirer une carte de plus ? (o/n) : ");
                scanf(" %c", &choix);


                if (choix == 'o') {
                    int nouvelleCarte = tirerCarte(cartejoueur);
                    printf("Vous avez tiré : %d\n", nouvelleCarte);
                    cartejoueur += nouvelleCarte;
                    Hand(&nouvelleCarte,1);
                    printf("Votre main : %d\n", cartejoueur);
                }
                else {
                    break;
                }
            }
        }
    }
    return cartejoueur;
}

int croupier(int cartebanque, int HandC[]) {
    int i = 2;
    while (cartebanque < 17) {
        sleep(1);
        int nouvelleCarte = tirerCarte(cartebanque);
        HandC[i] = nouvelleCarte;
        i += 1;
        printf("Le croupier a tiré : %d\n", nouvelleCarte);
        cartebanque += nouvelleCarte;
    }
    Hand(HandC,i);
    printf("Main du croupier : %d\n", cartebanque);
    return cartebanque;
}

float mise() {
    float bet;

    do {
        printf("Quel est votre mise ? ");
        if (scanf("%f", &bet) != 1) {
            // Si la saisie n'est pas un nombre
            printf("Veuillez entrer un montant valide.\n");
            // Efface le tampon d'entrée pour éviter une boucle infinie en cas de saisie non numérique
            while (getchar() != '\n');
            continue;  // Retourne à la demande de mise
        }

        if (bet < MISE_MINI) {
            printf("La mise minimale est de 10$\n");
        } else {
            return bet;
        }

    } while (1);  // Répète jusqu'à ce qu'une mise valide soit saisie

    return 0;  // Cette ligne ne sera jamais atteinte, ajoutée pour éviter un avertissement du compilateur
}

void printColor(const char *value, const char *suit, int type) //type = 1 pour print une value 0 pour une couleur
{
    const char *color;

    if(strcmp(suit, "♥") == 0)
        color = RED;
    else if (strcmp(suit, "♣") == 0)
        color = GRN;
    else if (strcmp(suit, "♦") == 0)
        color = CYA;
    else
        color = WHT;
    if(type)
        printf("%s%-2s\033[0m", color, value);
    else
        printf("%s%s\033[0m", color, suit);
        
}

void Hand(int Hand[],int compteur) {
    const char *suits[4] = {"♥", "♠", "♦", "♣"};
    

    for (int j = 0; j< compteur; j++) {
        sleep(1);
        const char *colori = suits[rand()% 4];

        if (Hand[j] == 11 || Hand[j] == 1) {
            const char *value = "A";

            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte
            printf("|  ");
            printColor(value, colori, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
        else if (Hand[j] == 10) {
            const char *valeur[4] = {"10", "J", "Q", "K"};
            const char *value = valeur[rand()%3];
            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte
            printf("|  ");
            printColor(value, colori, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
        else {
            char value[3]; // Assuming the maximum length of the value is 2 digits
            sprintf(value, "%d", Hand[j]);

            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte 
            printf("|  ");
            printColor(value, colori, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(value, colori, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
    }
}

void assurance(float pari, float stack, int Maincroup[], int totjou[]){
    char assur;
    int totalCroup;
    printf("La banque a un as !\n");
    printf("Assurance ? (o/n)\n");
    scanf(" %c", &assur);
    if (strcmp(&assur, "o") == 0) {
        stack -= pari/2;
        printf("Vous avez choisi l'assurance en ajoutant la moitié de votre mise");
        totalCroup = Maincroup[0];
        Maincroup[1] = tirerCarte(totalCroup);
        totalCroup += Maincroup[1];        
        if (Maincroup[0] == 11 && Maincroup[1] == 10) {
            printf("Le croupier a BlackJack vous récupérez votre mise");
            rejouer(stack);
        }
        else {
            totjou[0] = tourjoueur(totjou[0], stack, pari, &pari);

            Hand(Maincroup, 2);
            printf("Main du croupier : %d\n\n", totalCroup);
               
            // Tour du croupier.
            totalCroup = croupier(totalCroup, Maincroup);


            // Détermination des gagnants.
            float update4 = gagnant(totjou[0], totalCroup, stack, pari);
            stack = update4;
            rejouer(stack);
        }
    }
}

float blackjack_game(float playerStack) {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    int totalJoueurs[MAX_JOUEURS] = {0};
    int totalCroupier = 0;
    int nombreJoueurs = 1;
    int HandCroupier[5];

    /*printf("Entrez le nombre de joueurs (1-%d) : ", MAX_JOUEURS);
    scanf("%d", &nombreJoueurs);

    if (nombreJoueurs < 1 || nombreJoueurs > MAX_JOUEURS) {
        printf("Nombre de joueurs non valide.\n");
        return playerStack;
    }*/ //Pour plus de 1 joueur -> pas développé mais prévu dans le code

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
            Hand(cartesJoueurs[i], 2);
            printf("Bravo joueur %d vous avez un BlackJack !\n", i+1);
            playerStack -= pari;
            playerStack += pari*2.5;
            printf("Votre nouveau stack est: %f\n",playerStack);
            rejouer(playerStack);
        }
    }

    totalCroupier += tirerCarte(totalCroupier);
    HandCroupier[0] = totalCroupier;
    Hand(HandCroupier,1);
    printf("Main du croupier: %d\n", totalCroupier);
    if (HandCroupier[0] == 11) {
        assurance(pari, playerStack, HandCroupier, &totalJoueurs[0]);
    }


    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Première carte du joueur %d : %d\n", i + 1, cartesJoueurs[i][0]);
    }
    
    HandCroupier[1] = tirerCarte(totalCroupier);
    totalCroupier += HandCroupier[1];


    for (int i = 0; i < nombreJoueurs; i++) {
        Hand(cartesJoueurs[i],2);
        printf("Deuxième carte du joueur %d : %d\n", i + 1, cartesJoueurs[i][1]);
    }

    for (int i = 0; i < nombreJoueurs; i++) {
        printf("Votre main : %d\n", totalJoueurs[i]);
    }

    // Tours des joueurs.
    for (int i = 0; i < nombreJoueurs; i++) {
        if (cartesJoueurs[i][0] == cartesJoueurs[i][1] && playerStack >= 2* pari) {
        char choix;
        printf("Joueur %d, vous avez deux cartes identiques. Voulez-vous split votre jeu en doublant votre mise ? (o/n) : ", i + 1);
        scanf(" %c", &choix);
            
            if (choix == 'o') {
                float doublage = pari*2;  // Doublez la mise.
                printf("Vous avez split votre jeu. Votre mise est maintenant de : %f\n", doublage);
                int jeu1 = totalJoueurs[i]/2;
                int jeu2 = totalJoueurs[i]/2;
                jeu1 += tirerCarte(jeu1);
                jeu2 += tirerCarte(jeu2);

                printf("Votre premier jeu est : %d\n", jeu1);
                printf("Votre deuxième jeu est : %d\n", jeu2);
                
                //Blackjack avec deux jeux
                jeu1 = tourjoueur(jeu1, playerStack, doublage, &doublage);
                jeu2 = tourjoueur(jeu2, playerStack, doublage, &doublage);
                
        
                printf("Main du croupier : %d\n\n", totalCroupier);
                Hand(HandCroupier, 2);
            
                // Tour du croupier.
                totalCroupier = croupier(totalCroupier, HandCroupier);

                // Détermination des gagnants.
                    float update1 = gagnant(jeu1,totalCroupier,playerStack,doublage);
                    playerStack = update1;
                    float update2 = gagnant(jeu2,totalCroupier,playerStack,doublage);
                    playerStack = update2;
                    rejouer(playerStack);

            }
            else {  //Cas carte identiques mais ne souhaite pas split
                totalJoueurs[i] = tourjoueur(totalJoueurs[i], playerStack, pari, &pari);

                Hand(HandCroupier, 2);
                printf("Main du croupier : %d\n\n", totalCroupier);
                
            
                // Tour du croupier.
                totalCroupier = croupier(totalCroupier, HandCroupier);

                // Détermination des gagnants.
                float update3 = gagnant(totalJoueurs[i], totalCroupier, playerStack, pari);
                playerStack = update3;
                rejouer(playerStack);
            }
        }
        else { //Cas classique du blackjack
            totalJoueurs[i] = tourjoueur(totalJoueurs[i], playerStack, pari, &pari);

            //Hand(HandCroupier, 2);
            printf("Main du croupier : %d\n\n", totalCroupier);
               
            // Tour du croupier.
            totalCroupier = croupier(totalCroupier, HandCroupier);


            // Détermination des gagnants.
            float update4 = gagnant(totalJoueurs[i], totalCroupier, playerStack, pari);
            playerStack = update4;
            rejouer(playerStack);
        }
    }
    return playerStack;
}