#include <SQLLITE/sqlite3.h>
#include "stdio.h"
#include <database.h>

void arrivee_joueur(char *nom_joueur, float *stack_joueur)
{
    float credits;
    int valid_input = 0;
    switch (check_player_in_db(nom_joueur, stack_joueur))
    {
    case 0:
    printf("Veuillez entrer votre crédit initial\n");
    do {
        if (scanf("%f", &credits) != 1 || credits <= 0) {
            // Si la saisie n'est pas un nombre 
            printf("Veuillez saisir un montant valide.\n");
            // Efface le tampon d'entrée pour éviter une boucle infinie en cas de saisie non numérique
            while (getchar() != '\n');
            continue;  // Retourne à la demande de mise
        }
        else {
            valid_input = 1; // Set the flag to true if the input is valid
        }
    } while (!valid_input);
    *stack_joueur = credits;
    break;

    case 1: break;
    case 2: 
    printf("Veuillez entrer votre crédit initial\n", nom_joueur);
    do {
        if (scanf("%f", &credits) != 1 || credits <= 0) {
            // Si la saisie n'est pas un nombre
            printf("Veuillez saisir un montant valide.\n");
            // Efface le tampon d'entrée pour éviter une boucle infinie en cas de saisie non numérique
            while (getchar() != '\n');
            continue;  // Retourne à la demande de mise
        }
        else {
                valid_input = 1; // Set the flag to true if the input is valid
            }
        } while (!valid_input);
    *stack_joueur = credits;
    break;
    default: break;
    }
}

void update_player_credit(char *nom_joueur, float *stack_joueur) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    char *err_msg = 0;
    int rc = sqlite3_open("casino.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Désole, nous ne trouvons pas la liste des VIP. Vos crédit ne seront pas enregistrés.\n(%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    const char *update_sql = "UPDATE joueur SET credits = ? WHERE nom = ?";
    rc = sqlite3_prepare_v2(db, update_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Désolé, nous avons plus de place sur la liste des VIP pour modifier vos crédits...\n(%s)\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;  // Ou gérer l'erreur de manière appropriée
    }

    // Liez les paramètres
    sqlite3_bind_double(stmt, 1, *stack_joueur);
    sqlite3_bind_text(stmt, 2, nom_joueur, -1, SQLITE_STATIC);

    // Exécutez la requête UPDATE
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Désolé, nous avons plus de place sur la liste des VIP pour modifier vos crédits...\n(%s)\n", sqlite3_errmsg(db));
    } else {
        printf("Nous avons bien modifié vos crédits sur la liste des VIP.\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int check_player_in_db(char *nom_joueur, float *stack_joueur) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *err_msg = 0;
    int rc = sqlite3_open("casino.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Désole, nous ne trouvons pas la liste des VIP...\n(%s)\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    // Préparez la requête SELECT
    const char *select_sql = "SELECT nom, credits FROM joueur WHERE nom = ?";
    rc = sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Désolé, nous n'arrivons pas à lire la liste des VIP... \n(%s)\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    // Liez le nom du joueur à la requête
    sqlite3_bind_text(stmt, 1, nom_joueur, -1, SQLITE_STATIC);
    // Exécutez la requête SELECT
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Le joueur existe dans la base de données
        *stack_joueur = sqlite3_column_double(stmt, 1);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
        // Vous pouvez maintenant utiliser les informations du joueur comme nécessaire
    }
    else if (rc == SQLITE_DONE) {
        // Le joueur n'a pas été trouvé dans la base de données
        printf("Bienvenue %s, votre nom n'est pas sur la liste des VIP, cela doit être votre première fois ici !\n\n", nom_joueur);
        // Réinitialisez la requête pour effectuer une insertion
        sqlite3_finalize(stmt);
        // Préparez la requête INSERT
        const char *insert_sql = "INSERT INTO joueur (nom, credits) VALUES (?, 0)";
        rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Désolé, le stylo n'a plus d'encre. Nous ne pouvons donc pas écrire votre nom sur la liste des VIP.\n(%s)\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 0;
        }
        // Liez le nom du joueur à la requête INSERT
        sqlite3_bind_text(stmt, 1, nom_joueur, -1, SQLITE_STATIC);
        // Exécutez la requête INSERT
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Désolé, le stylo n'a plus d'encre. Nous ne pouvons donc pas écrire votre nom sur la liste des VIP.\n(%s)\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
        else {
            printf("Nous vous avons ajouté sur la liste des VIP, vous pourrez laisser vos crédits entre deux parties !\n");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 2;
        }
    }
    else {
        fprintf(stderr, "Désolé mais nous ne trouvons pas la liste des VIP...\n(%s)\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    // Finalisez la requête et fermez la base de données
}