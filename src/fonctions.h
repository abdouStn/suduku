/**
 *\file fonctions.h
 *\brief Sudoku
 *\author Abdoulaye Diallo, Redoine El Ouasti, Simon Galand, Adrien Lamant, Pierre-Louis Latour, Charly Maeder, Pierre Ruffin, Stella Zevio
 *\version 0.2
 *\date 2014-03-26
 *
 * Sudoku en C (resolution des grilles 4x4, 9x9, 16x16 et jeu).
 *
 */ 


#ifndef FONCTIONS_H
#define FONCTIONS_H


#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>	
#include <string.h>

#include "color.h"


#define COULEUR_BLEU 	printf(BLUE);
#define COULEUR_VERTE 	printf(GREEN);
#define COULEUR_ORIGINE printf(DEFAULT_COLOR);

#define COULEUR_ROUGE 	fprintf(stderr, RED);
#define FLUSH_COULEUR_ORIGINE fprintf(stderr, DEFAULT_COLOR);

/**
 * \author Stella Zevio
 * \struct caseGrille
 * \brief La structure "caseGrille" modelise une case d'une grille de sudoku. On utilise un uint16_t code sur 16 bits.
 */

typedef struct{
	uint16_t aide; /*!< sert a stocker dans les bits les valeurs possibles associees a la case */
	uint8_t valeur; /*!< la valeur de la case entree par l'utilisateur */
	uint8_t modifiable; /*!< un pseudo-booleen, 1 si la case est une case modifiable de la grille de jeu, 0 sinon (si sa valeur est fixee lors de la generation de la grille de jeu et donc non modifiable) */
}caseGrille;


/**
 * \author Abdoulaye Diallo, Stella Zevio
 * \fn size_t initTaille(void)
 * \brief La fonction "initTaille" initialise la taille de la grille de sudoku.
 * \return taille - la taille de la grille de sudoku.
 */

size_t initTaille();


/**
 * \author Stella Zevio
 * \fn caseGrille** initGrille(size_t taille) 
 * \brief La fonction "initGrille" initialise la grille de sudoku (qui est un tableau a deux dimensions de cases de grille de sudoku), en fonction de la taille passee en parametre.
 * \param taille - la taille de la grille.
 * \return grille - la grille de sudoku, qui est un tableau a deux dimensions.
 */

caseGrille** initGrille(size_t taille);


/**
 * \author Abdoulaye Diallo, Stella Zevio
 * \fn void afficheGrille(caseGrille **grille, size_t taille) 
 * \brief La fonction "afficheGrille" affiche la grille de sudoku passee en parametre.
 * \param grille - la grille, qui est un tableau a deux dimensions.
 * \param taille - la taille de la grille.
 */

void afficheGrille(caseGrille **grille, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurLigne(int valeur, caseGrille **grille, int ligne, size_t taille) 
 * \brief La fonction "absentSurLigne" permet de verifier si la valeur que l'on veut affecter a une case est presente sur la ligne de la case testee.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param ligne - la ligne a tester.
 * \param valeur - la valeur a tester.
 * \return 1 si la valeur est absente de la ligne.
 * \return 0 si la valeur est presente sur la ligne.
*/

int absentSurLigne (uint8_t valeur, caseGrille **grille, size_t ligne, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurColonne(int valeur, caseGrille **grille, int colonne, size_t taille) 
 * \brief La fonction "absentSurColonne" permet de verifier si la valeur que l'on veut affecter a une case est presente sur la colonne de la case testee.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param colonne - la colonne a tester.
 * \param valeur - la valeur a tester.
 * \return 1 si la valeur est absente de la colonne.
 * \return 0 si la valeur est presente sur la colonne.
*/

int absentSurColonne (uint8_t valeur, caseGrille **grille, size_t colonne, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurRegion(int valeur, caseGrille **grille, int ligne, int colonne, size_t taille) 
 * \brief La fonction "absentSurRegion" permet de verifier si la valeur que l'on veut affecter a une case est presente sur la zone de la case testee.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param ligne -la ligne a tester.
 * \param colonne - la colonne a tester.
 * \param valeur - la valeur a tester.
 * \return 1 si la valeur est absente de la region.
 * \return 0 si la valeur est presente sur la region.
*/

int absentSurRegion (uint8_t valeur, caseGrille **grille, size_t ligne, size_t colonne, size_t taille);


/**
 * \author Stella Zevio
 * \fn void echange(uint8_t *a, uint8_t *b)
 * \brief La fonction "echange" permet d'echanger deux valeurs.
 * \param a - la premiere valeur a echanger.
 * \param b - la deuxieme valeur a echanger.
*/

void echange(uint8_t *a, uint8_t *b);


/**
 * \author Stella Zevio
 * \fn void melangerTableauValeurs(void)
 * \brief La fonction "melangerTableauValeurs" permet de rendre pseudo-aleatoires les valeurs possibles pour remplir la grille. Elle permet de melanger les valeurs de notre tableau global de valeurs possibles.
*/

void melangerTableauValeurs(uint8_t *tableauValeurs, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Stella Zevio
 * \fn bool genererGrilleComplete(caseGrille **grille, int position, size_t taille) 
 * \brief La fonction "genererGrilleComplete" permet la generation de la grille complete de sudoku par le principe du backtracking (retour sur trace).
 * \param grille - la grille.
 * \param position - la position de la case qui est testee (ligne*colonne).
 * \param taille - la taille de la grille.
 * \return true si la grille est correctement generee.
 * \return false si la grille n'est pas correctement generee.
*/

bool genererGrilleComplete(caseGrille **grille, size_t position, size_t taille, uint8_t *tableauValeurs);


/**
 * \author Stella Zevio
 * \fn void genererGrilleJeu(caseGrille** grille, size_t taille) 
 * \brief La fonction "genererGrilleJeu" permet la generation de la grille de jeu en trouant la grille complete (grille de solution).
 * \param grille - la grille.
 * \param taille - la taille de la grille.
*/

void genererGrilleJeu(caseGrille** grille, size_t taille, uint8_t* tableauValeurs);


/**
 * \author Redoine El Ouasti, Stella Zevio
 * \fn int jouer(caseGrille **grille, size_t taille)
 * \brief La fonction "jouer" permet de modifier les valeurs associees aux cases de grille.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
*/

void jouer(caseGrille **grille, size_t taille);


/**
 * \author Redoine El Ouasti
 * \fn int comparaisonGrilles(caseGrille ** premiereGrille, caseGrille ** deuxiemeGrille, size_t taille) 
 * \brief La fonction "comparaisonGrilles" permet de comparer deux grilles de sudoku.
 * \param premiereGrille - l'une des grilles que l'on veut comparer.
 * \param deuxiemeGrille - l'autre grille que l'on veut comparer.
 * \param taille - la taille des grilles.
 * \return 1 si les grilles sont identiques.
 * \return 0 si les grilles sont differentes.
*/

int comparaisonGrilles(caseGrille ** premiereGrille, caseGrille ** deuxiemeGrille, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant
 * \fn void sauvegarde(caseGrille** grille, caseGrille** grilleSolution, size_t taille, float temps)
 * \brief La fonction "sauvegarde" permet de sauvegarder une partie.
 * \param grille - la grille de jeu.
 * \param grilleSolution - la solution de la grille de jeu (la grille complete).
 * \param taille - la taille des grilles.
 * \param temps - le temps passe a resoudre le sudoku.
*/

void sauvegarde(caseGrille** grille, caseGrille **grilleSolution, size_t taille, float temps);


/**
 * \author Abdoulaye Diallo, Adrien Lamant
 * \fn bool chargerPartie(size_t taille, caseGrille **grilleSolution, caseGrille **grille, float* temps)
 * \brief La fonction "chargerPartie" permet de charger une partie.
 * \param taille - la taille des grilles.
 * \param grilleSolution - la solution de la grille de jeu (la grille complete).
 * \param grille - la grille de jeu.
 * \param temps - le temps passe a resoudre le sudoku.
 * \return true si la grille est chargeable
 * \return false sinon.
*/

bool chargerPartie(size_t taille, caseGrille **grilleSolution, caseGrille **grille, float* temps);


/**
 * \author Pierre Ruffin
 * \fn void reinitialiserPartie (caseGrille **grille, size_t taille)
 * \brief La fonction "reinitialiserPartie" permet de reinitialiser la grille de jeu comme en debut de partie.
 * \param grille - la grille a modifier.
 * \param taille - la taille des grilles.
 */

void reinitialiserPartie (caseGrille **grille, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin, Stella Zevio
 * \fn bool estInclus(unsigned short case1, unsigned short case2, size_t taille)
 * \brief La fonction "estInclus" permet de verifier qu'un singleton (une unique valeur possible d'une case) est present ailleurs dans les possibilites des cases contenues dans sa ligne, colonne ou region.
 * \param singleton - le singleton.
 * \param possibilitesCase - l'ensemble des possibilites de la case a tester.
 * \param taille - la taille des grilles.
 * \return true si le singleton est present ailleurs dans les possibilites des cases de la ligne/colonne/region.
 * \return false sinon.
*/

bool estInclus(uint16_t singleton, uint16_t possibilitesCase, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin, Stella Zevio
 * \fn bool crossHatching(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "crossHatching" permet d'eliminer un singleton des possibilites des autres cases de sa sous-grille.
 * \param sousGrille - la sous-grille a tester.
 * \param taille - la taille des grilles.
 * \return true - si cross-hatching s'applique.
 * \return false - sinon.
*/

bool crossHatching(caseGrille *sousGrille, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn bool loneNumber(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "loneNumber" est une heuristique qui permet de transformer une aide en singleton si une de ces valeurs n'est pas presente dans les autres cases.
 * \param sousGrille - la sous-grille a tester.
 * \param taille - la taille des grilles.
 * \return true - si lone-number s'applique.
 * \return false - sinon.
 */

bool loneNumber(caseGrille *sousGrille, size_t taille);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn int nbValeurs(unsigned short aide)
 * \brief La fonction "nbValeurs" permet de connaitre le nombre de bits a 1 pour un unsigned short representant le nombre de valeurs d'une liste de possibilites.
 * \param aide - la liste de possibilite a denombrer.
 * \return nbval - le nombre de valeurs d'une liste de possibilites.
*/

int nbValeurs(unsigned short aide);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn int nbOccurence(caseGrille *sousGrille,int indice, size_t taille)
 * \brief La fonction "nbOccurence" permet de connaitre le nombre de fois qu'une liste de possibilites apparait. Si elle n'apparait qu'une fois, cela renvoie 0.
 * \param *sousGrille - l'ensemble de listes de possibilites.
 * \param indice - l'indice de la case qu'on cherche a denombrer.
 * \param taille - la taille des grilles.
 * \return nbocc - le nombre d'occurrences d'une liste de possibilites.
*/

int nbOccurence(caseGrille *sousGrille,int indice, size_t taille);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn bool nakedSubset(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "nakedSubset" permet de retirer une liste de possibilite si elle repond au Naked Subset, et de renvoyer un booleen temoignant ou non de l'application de cette regle.
 * \param *sousGrille - l'ensemble des listes de possibilites.
 * \param taille - la taille des grilles.
 * \return true - si naked subset s'applique
 * \return false - sinon
*/

bool nakedSubset(caseGrille *sousGrille, size_t taille);


/**
 * \author Charly Maeder
 * \fn caseGrille** convertirZoneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);
 * \brief La fonction "convertirZoneEnTableau" permet de convertir une zone de la grille en tableau.
 * \param grille - la grille de jeu.
 * \param ligne - la ligne de la grille où se trouve la case où on veut l'aide.
 * \param colonne - la colonne de la grille où se trouve la case où on veut l'aide.
 * \param taille - la taille de la grille.
 * \return tableau - tableau correspondant à la zone que l'on voulait convertir.
 */

caseGrille** convertirZoneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);


/**
 * \author Charly Maeder
 * \fn caseGrille** convertirColonneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);
 * \brief La fonction "convertirColonneEnTableau" permet de convertir une colonne de la grille en tableau.
 * \param grille - la grille de jeu.
 * \param ligne - la ligne de la grille où se trouve la case où on veut l'aide.
 * \param colonne - la colonne de la grille où se trouve la case où on veut l'aide.
 * \param taille - la taille de la grille.
 * \return tableau - tableau correspondant a la colonne que l'on voulait convertir.
 */

caseGrille** convertirColonneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn void initAide(caseGrille** grille, size_t taille);
 * \brief La fonction "initAide" permet d'initialiser l'aide en fonction des valeurs des cases.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 */

void initAide(caseGrille** grille, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn void aide(caseGrille** grille, const size_t taille);
 * \brief La fonction "aide" permet de creer l'aide pour l'ensemble de la grille.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 */

void aide(caseGrille** grille, const size_t taille);


/**
 * \author Pierre Ruffin, Charly Maeder
 * \fn void parcoursGrilleAide(caseGrille** grille, size_t taille, size_t ligne, size_t colonne);
 * \brief La fonction "parcoursGrilleAide" permet d'appliquer les heuristiques sur l'ensemble de la grille.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 * \param ligne - la ligne de la case où on veut l'aide.
 * \param colonne - la colonne de la case où on veut l'aide.
 */

void parcoursGrilleAide(caseGrille** grille, size_t taille, size_t ligne, size_t colonne);


/**
 * \author Stella Zevio
 * \fn void echangeInt(int *a, int *b)
 * \brief La fonction "echangeInt" permet d'echanger deux entiers.
 * \param a - le premier entier que l'on souhaite echanger.
 * \param b - le deuxieme entier que l'on souhaite echanger.
*/

void echangeInt(int *a, int *b);


/**
 * \author Stella Zevio
 * \fn int insererPetiteValeur(int* T, char noms[10][30], int val, char nom[30])
 * \brief La fonction "insererPetiteValeur" permet d'inserer une valeur val si elle est la plus petite parmi tous les elements du tableau T.
 * \param T - un tableau d'entier.
 * \param noms - Un tableau de char[30].
 * \param val - Un entier qui est la valeur a inserer.
 * \param nom - une chaine de caracteres qui est le nom a inserer.
 * \return trouve - la position de la valeur a modifier
 * \return -1 - s'il n'y a pas de valeur a modifier
*/

int insererPetiteValeur(int* T, char noms[10][30], int val, char nom[30]);


/**
 * \author Stella Zevio
 * \fn void demanderNom(char *nom)
 * \brief La fonction "demanderNom" permet de demander et de renvoyer une chaine de caracteres.
 * \param nom - Une chaine de caractere.
*/

void demanderNom(char *nom);


/**
 * \author Stella Zevio
 * \fn void score(int temps, size_t taille)
 * \brief La fonction "score" permet de verifier s'il y a un nouveau score.
 * \param temps - le temps passe a resoudre la grille. 
 * \param taille - la taille de la grille.
*/

void score(int temps, size_t taille);


/**
 * \author Stella Zevio
 * \fn void reinitialiserTop10(size_t taille)
 * \brief La fonction "reinitialiserTop10" permet de reinitialiser le score dans les fichers Top10_4.txt, Top10_9.txt,  Top10_16.txt
 * \param taille - la taille de la grille.
*/

void reinitialiserTop10(size_t taille);


/**
 * \author Stella Zevio
 * \fn void afficherTop10(size_t taille)
 * \brief La fonction "afficherTop10" permet d'afficher le Top 10 d'une taille de grille donnee.
 * \param taille - la taille de la grille.
*/

void afficherTop10(size_t taille);


/**
 * \author Stella Zevio
 * \fn void recupeGrille(caseGrille**grille, size_t taille)
 * \brief La fonction "recupeGrille" permet de recuperer une grille ecrite dans un fichier.
 * \param grille - la grille que l'on souhaite recuperer.
*/

void recupeGrille(caseGrille**grille, size_t taille);


/**
 * \author Redoine El Ouasti, Stella Zevio
 * \fn void libereGrille(caseGrille** grille, size_t taille)
 * \brief La fonction "libereGrille" permet de liberer en memoire les grilles allouees dynamiquement.
 * \param grille - la grille a liberer.
 * \param taille - La taille de la grille.
*/

void libereGrille(caseGrille** grille, size_t taille);


/**
 * \author Stella Zevio
 * \fn void purger(void)
 * \brief La fonction "purger" permet de vider le buffer.
*/

void purger(void);


/**
 * \author Stella Zevio
 * \fn void clean (char *chaine)
 * \brief La fonction "clean" permet d'eliminer un retour a la ligne a la fin de chaine passee en parametre et vide le buffer.
 * \param chaine - la chaine passee en parametre.
*/

void clean (char *chaine);


/**
 * \author Redoine El Ouasti, Stella Zevio
 * \fn size_t saisie(void)
 * \brief La fonction "saisie" permet de renvoyer la valeur saisie par l'utilisateur.
 * \return entier - valeur saisie par l'utilisateur.
*/

size_t saisie(void);

#endif
