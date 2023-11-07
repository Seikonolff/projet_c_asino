#include "poker.h"
#include <stdlib.h>
#include <stdio.h>

#define CLUBS    0x8000
#define DIAMONDS 0x4000
#define HEARTS   0x2000
#define SPADES   0x1000

const int prime_numbers[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

// Attribuer à chaque carte un iddentifiant unique codé sur 32 bit 
int getCardIdentifier(int rank, int suit) {
    int card = 0;
    switch (suit)
    {
    case 0 :
        suit = HEARTS;
        break;
    case 1 :
        suit = SPADES;
        break;
    case 2 :
        suit = DIAMONDS;
        break;
    case 3 :
        suit = CLUBS;
        break;
    
    default:
        break;
    }

    // Les bits pour le rang spécifique (un seul bit défini parmi les 13 premiers bits)
    card |= 1 << (rank + 16); // Le décalage de 16 pour les 2 octets du milieu

    card |= suit;

    // Les bits pour le rang numérique
    card |= rank << 8; // Le décalage de 8 pour l'octet le plus à gauche

    // Les bits pour le nombre premier associé au rang de la carte
    card |= prime_numbers[rank];

    return card;
}

/*
int makeCard(int rank, char suit) {
    int card = 0;
    int suitBit = 0;

    switch (suit) {
        case 'c': suitBit = CLUBS; break;
        case 'd': suitBit = DIAMONDS; break;
        case 'h': suitBit = HEARTS; break;
        case 's': suitBit = SPADES; break;
    }

    card |= suitBit; // Set the suit bit
    card |= (1 << (rank + 16)); // Set the bit for the rank (offset by 16 to match the diagram)
    card |= prime_numbers[rank]; // Set the prime number for the rank

    return card;
}

int makeCard2(int rank, char suit) {
    int card = 0;
    int suitValue = 0;

    // Les bits pour le rang spécifique (un seul bit défini parmi les 13 premiers bits)
    card |= 1 << (rank + 16); // Le décalage de 16 pour les 2 octets du milieu

    // Définir les bits pour la couleur
    switch (suit) {
        case 'c': suitValue = 0x8000; break; // bit pattern 1000 pour les clubs (trèfles)
        case 'd': suitValue = 0x4000; break; // bit pattern 0100 pour les diamonds (carreaux)
        case 'h': suitValue = 0x2000; break; // bit pattern 0010 pour les hearts (coeurs)
        case 's': suitValue = 0x1000; break; // bit pattern 0001 pour les spades (piques)
    }
    card |= suitValue;

    // Les bits pour le rang numérique
    card |= rank << 8; // Le décalage de 8 pour l'octet le plus à gauche

    // Les bits pour le nombre premier associé au rang de la carte
    card |= prime_numbers[rank]; // Pas de décalage nécessaire pour l'octet le plus à droite

    return card;
}


int main() {
    // Exemple d'utilisation :
    int card1 = getCardIdentifier(2, SPADES); // 2 de Pique
    int card2 = getCardIdentifier(14, HEARTS); // As de Coeur

    printf("Identifiant pour 2 de Pique: %d\n", card1);
    printf("Identifiant pour As de Coeur: %d\n", card2);

    return 0;
}
*/

