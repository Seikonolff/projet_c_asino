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

#define NB_CARTES 52



void initialiserCartes(Carte jeu[]) {
    const char *noms[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const char *couleurs[] = {"♥", "♠", "♦", "♣"};

    int indice = 0;

    for (int valeur = 1; valeur <= 13; valeur++) {
        for (int couleur = 0; couleur < 4; couleur++) {
            jeu[indice].valeur = (valeur == 1) ? 11 : (valeur > 10) ? 10 : valeur;
            jeu[indice].nom = noms[valeur - 1];
            jeu[indice].couleur = couleurs[couleur];
            indice++;
        }
    }
}

void melangerCartes(Carte jeu[]) {
    for (int i = NB_CARTES - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Échange des cartes i et j
        Carte temp = jeu[i];
        jeu[i] = jeu[j];
        jeu[j] = temp;
    }
}

Carte tirerCarte(Carte jeu[], int *indice) {
    Carte carte = jeu[*indice];
    (*indice)++;
    return carte;
}

// Fonction pour tirer une carte aléatoire entre 2 et 11 (as vaut 11 par défaut).
/*int tirerCarte(int tot) {
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
}*/

void rejouer(float newstack) {
    char jouer;
    printf("Voulez-vous rejouer ? (o/n)\n");
    scanf(" %c",&jouer);
    if (jouer == 'o') {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    blackjack_game(newstack);
    }
    else {
        printf("Merci d'avoir joué !\n");
        return;
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

int tourjoueur(int cartejoueur, int stackjoueur, float parijoueur, float *ptr, Carte jeu[], int *indicecarte, Carte mainjoueur[]) {
    int doubler = 0;
    int j = 2;
    while (cartejoueur < 21) {
        sleep(1);
        if (doubler == 0 && stackjoueur >= 2*parijoueur) { //Possibilité de doubler car stack suffisant
            char choix;
            printf("Voulez-vous tirer une carte de plus ou doubler ? (o/n/d) : ");
            scanf(" %c", &choix);

            if (choix == 'o') {
                mainjoueur[j] = tirerCarte(jeu, indicecarte);
                printf("Vous avez tiré : %d\n", mainjoueur[j].valeur);
                cartejoueur += mainjoueur[j].valeur;
                j += 1;
                if (cartejoueur > 21) {
                    for (int i = 0; i <= j; i++) {
                        if (mainjoueur[i].valeur == 11) {
                            cartejoueur -= mainjoueur[i].valeur;
                            mainjoueur[i].valeur = 1;
                            cartejoueur += mainjoueur[i].valeur;
                        }
                    }
                }
                Hand(mainjoueur,j);
                printf("Votre main : %d\n", cartejoueur);
            } else if (choix == 'd'){
                mainjoueur[j] = tirerCarte(jeu, indicecarte);
                cartejoueur += mainjoueur[j].valeur;
                if (cartejoueur > 21) {
                    for (int i = 0; i <= j; i++) {
                        if (mainjoueur[i].valeur == 11) {
                            cartejoueur -= mainjoueur[i].valeur;
                            mainjoueur[i].valeur = 1;
                            cartejoueur += mainjoueur[i].valeur;
                        }
                    }
                }
                *ptr += parijoueur;
                printf("Votre mise est maintenant de : %f\n", *ptr);
                printf("Vous avez tiré : %d\n", mainjoueur[j].valeur);
                Hand(mainjoueur,j+1);
                printf("Votre main : %d\n", cartejoueur);
                break;
            }
            else {
                break;
            }
            doubler = 1;
        }
        else { //Joueur ne peut pas doubler car il n'a pas le stack suffisant ou il a déjà doublé ou tiré
            char choix;
            printf("Voulez-vous tirer une carte de plus ? (o/n) : ");
            scanf(" %c", &choix);

            if (choix == 'o') {
                mainjoueur[j] = tirerCarte(jeu, indicecarte);
                printf("Vous avez tiré : %d\n", mainjoueur[j].valeur);
                cartejoueur += mainjoueur[j].valeur;
                j += 1;
                if (cartejoueur > 21) {
                    for (int i = 0; i <= j; i++) {
                        if (mainjoueur[i].valeur == 11) {
                            cartejoueur -= mainjoueur[i].valeur;
                            mainjoueur[i].valeur = 1;
                            cartejoueur += mainjoueur[i].valeur;
                        }
                    }
                }
                Hand(mainjoueur,j);
                printf("Votre main : %d\n", cartejoueur);
            }
            else {
                break;
            }
        }
    }
    return cartejoueur;
}

int croupier(int cartebanque, Carte HandC[], Carte jeu[], int *indicecarte) {
    int j = 2;
    while (cartebanque < 17) {
        sleep(1);
        HandC[j] = tirerCarte(jeu, indicecarte);
        printf("Le croupier a tiré : %d\n", HandC[j].valeur);
        cartebanque += HandC[j].valeur;
        j += 1;
        if (cartebanque > 21) {
            for (int i = 0; i <= j; i++) {
                if (HandC[i].valeur == 11) {
                    cartebanque -= HandC[i].valeur;
                    HandC[i].valeur = 1;
                    cartebanque += HandC[i].valeur;
                }
            }
        }    
        Hand(HandC,j);
        printf("Main du croupier : %d\n", cartebanque);
    }
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

void Hand(Carte Hand[],int compteur) {

    for (int j = 0; j< compteur; j++) {
        sleep(1);

        if (Hand[j].valeur == 11 || Hand[j].valeur == 1) {

            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte
            printf("|  ");
            printColor(Hand[j].nom, Hand[j].couleur, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
        else if (Hand[j].valeur == 10) {

            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte
            printf("|  ");
            printColor(Hand[j].nom, Hand[j].couleur, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
        else {

            // Imprime le haut de chaque carte
            printf("+-----+ ");
            printf("\n");

            // Imprime la valeur et le haut de la couleur de chaque carte
            printf("|");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("   | ");
            printf("\n");

            // Imprime la couleur de chaque carte 
            printf("|  ");
            printColor(Hand[j].nom, Hand[j].couleur, 0); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("  | ");
            printf("\n");

            // Imprime la valeur et le bas de la couleur de chaque carte
            printf("|   ");
            printColor(Hand[j].nom, Hand[j].couleur, 1); // %-2s pour aligner les valeurs à gauche avec deux caractères
            printf("| ");
            printf("\n");

            // Imprime le bas de chaque carte
            printf("+-----+ ");
            printf("\n");
        }
    }
}

void assurance(float pari, float stack, Carte Maincroup[], int totjou, Carte jeu[], int *indicecarte, Carte mainjou[]) {
    char assur;
    int totalCroup;
    printf("La banque a un as !\n");
    printf("Assurance ? (o/n)\n");
    scanf(" %c", &assur);
    if (assur == 'o') {
        stack -= pari/2;
        printf("Vous avez choisi l'assurance en ajoutant la moitié de votre mise\n");
        totalCroup = Maincroup[0].valeur;
        Maincroup[1] = tirerCarte(jeu, indicecarte);
        totalCroup += Maincroup[1].valeur;        
        if (Maincroup[0].valeur == 11 && Maincroup[1].valeur == 10) {
            Hand(Maincroup,2);
            printf("Le croupier a BlackJack vous récupérez votre mise\n");
            rejouer(stack);
        }
        else {
            Hand(mainjou,2);
            totjou = tourjoueur(totjou, stack, pari, &pari, jeu, indicecarte, mainjou);

            Hand(Maincroup, 2);
            printf("Main du croupier : %d\n\n", totalCroup);
               
            // Tour du croupier.
            totalCroup = croupier(totalCroup, Maincroup, jeu, indicecarte);


            // Détermination des gagnants.
            float update4 = gagnant(totjou, totalCroup, stack, pari);
            stack = update4;
            rejouer(stack);
        }
    }
}

float blackjack_game(float playerStack) {
    // Initialisation du générateur de nombres aléatoires.
    srand(time(NULL));

    Carte jeu[NB_CARTES];
    int totalJoueurs = 0;
    Carte cartescroupier[7];
    int totalCroupier = 0;
    int nombreJoueurs = 1;
    int indicecarte = 0;

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

    
    initialiserCartes(jeu);
    melangerCartes(jeu);

    float pari = mise();
    
    Carte cartesJoueurs[7];  // Tableau pour stocker les cartes des joueurs.

    // Distribution des cartes initiales pour chaque joueur et le croupier.
    
    cartesJoueurs[0] = tirerCarte(jeu, &indicecarte);
    cartesJoueurs[1] = tirerCarte(jeu, &indicecarte);
    totalJoueurs = cartesJoueurs[0].valeur + cartesJoueurs[1].valeur;
    if (totalJoueurs == 21)
    {
        printf("Votre main est : %d\n", totalJoueurs);
        Hand(cartesJoueurs, 2);
        printf("Bravo joueur vous avez un BlackJack !\n");
        playerStack -= pari;
        playerStack += pari*2.5;
        printf("Votre nouveau stack est: %f\n",playerStack);
        rejouer(playerStack);
    }

    cartescroupier[0] = tirerCarte(jeu, &indicecarte);
    totalCroupier += cartescroupier[0].valeur;
    Hand(cartescroupier,1);
    printf("Main du croupier: %d\n", totalCroupier);
    if (cartescroupier[0].valeur == 11) {
        assurance(pari, playerStack, cartescroupier, totalJoueurs, jeu, &indicecarte, cartesJoueurs);
    }

    printf("Votre première carte est : %s de %s\n", cartesJoueurs[0].nom, cartesJoueurs[0].couleur);
    
    cartescroupier[1] = tirerCarte(jeu, &indicecarte);
    totalCroupier += cartescroupier[1].valeur;


    Hand(cartesJoueurs,2);
    printf("Votre deuxième carte est : %s de %s\n", cartesJoueurs[1].nom, cartesJoueurs[1].couleur);


    printf("Votre main : %d\n", totalJoueurs);

    // Tours des joueurs.
    if (cartesJoueurs[0].valeur == cartesJoueurs[1].valeur && playerStack >= 2* pari) {
    char choix;
    printf("Vous avez deux cartes identiques. Voulez-vous split votre jeu en doublant votre mise ? (o/n) : ");
    scanf(" %c", &choix);            
        if (choix == 'o') {
            float doublage = pari*2;  // Doublez la mise.
            Carte main1[7];
            Carte main2[7];
            printf("Vous avez split votre jeu. Votre mise est maintenant de : %f\n", doublage);
            main1[0] = cartesJoueurs[0];
            main2[0] = cartesJoueurs[1];
            main1[1] = tirerCarte(jeu, &indicecarte);
            main2[1] = tirerCarte(jeu, &indicecarte);
            int tot1 = main1[0].valeur + main1[1].valeur;
            int tot2 = main2[0].valeur + main2[1].valeur;
            
            Hand(main1, 2);
            printf("Votre premier jeu est : %d\n", tot1);
            Hand(main2, 2);
            printf("Votre deuxième jeu est : %d\n", tot2);
                
            //Blackjack avec deux jeux
            tot1 = tourjoueur(tot1, playerStack, doublage, &doublage, jeu, &indicecarte,main1);
            tot2 = tourjoueur(tot2, playerStack, doublage, &doublage, jeu, &indicecarte,main2);
                
        
            printf("Main du croupier : %d\n\n", totalCroupier);
            Hand(cartescroupier, 2);
            
            // Tour du croupier.
            totalCroupier = croupier(totalCroupier, cartescroupier, jeu, &indicecarte);

            // Détermination des gagnants.
            float update1 = gagnant(tot1,totalCroupier,playerStack,pari);
            playerStack = update1;
            float update2 = gagnant(tot2,totalCroupier,playerStack,pari);
            playerStack = update2;
            rejouer(playerStack);

        }
        else {  //Cas carte identiques mais ne souhaite pas split
            totalJoueurs = tourjoueur(totalJoueurs, playerStack, pari, &pari, jeu, &indicecarte,cartesJoueurs);

            Hand(cartescroupier, 2);
            printf("Main du croupier : %d\n\n", totalCroupier);
                
            
            // Tour du croupier.
            totalCroupier = croupier(totalCroupier, cartescroupier, jeu, &indicecarte);

            // Détermination des gagnants.
            float update3 = gagnant(totalJoueurs, totalCroupier, playerStack, pari);
            playerStack = update3;
            rejouer(playerStack);
        }
    }
    else { //Cas classique du blackjack
        totalJoueurs = tourjoueur(totalJoueurs, playerStack, pari, &pari, jeu, &indicecarte, cartesJoueurs);

        Hand(cartescroupier, 2);
        printf("Main du croupier : %d\n\n", totalCroupier);
           
        // Tour du croupier.
        totalCroupier = croupier(totalCroupier, cartescroupier, jeu, &indicecarte);


        // Détermination des gagnants.
        float update4 = gagnant(totalJoueurs, totalCroupier, playerStack, pari);
        playerStack = update4;
        rejouer(playerStack);
    }
    return playerStack;
}