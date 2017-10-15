/**
 *\file fonctions.h
 *\brief Sudoku
 *\author Abdoulaye Diallo, Redoine El Ouasti, Simon Galand, Adrien Lamant, Pierre-Louis Latour, Charly Maeder, Pierre Ruffin, Stella Zevio
 *\version 0.2
 *\date 2014-03-26
 *
 * Sudoku en C : résolution des grilles 4x4, 9x9, 16x16 et jeu.
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
 * \brief La structure "caseGrille" modélise une case d'une grille de sudoku. On utilise un uint16_t codé sur 16 bits.
 */

typedef struct{
	uint16_t aide; /*!< sert à stocker dans les bits les valeurs possibles associées à la case */
	uint8_t valeur; /*!< la valeur de la case entrée par l'utilisateur */
	uint8_t modifiable; /*!< un pseudo-booléen, 1 si la case est une case modifiable de la grille de jeu, 0 sinon (si sa valeur est fixée lors de la génération de la grille de jeu et donc non modifiable) */
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
 * \brief La fonction "initGrille" initialise la grille de sudoku (qui est un tableau à deux dimensions de cases de grille de sudoku), en fonction de la taille passée en paramètre.
 * \param taille - la taille de la grille.
 * \return grille - la grille de sudoku, qui est un tableau à deux dimensions.
 */

caseGrille** initGrille(size_t taille);


/**
 * \author Abdoulaye Diallo, Stella Zevio
 * \fn void afficheGrille(caseGrille **grille, size_t taille) 
 * \brief La fonction "afficheGrille" affiche la grille de sudoku passée en paramètre.
 * \param grille - la grille, qui est un tableau à deux dimensions.
 * \param taille - la taille de la grille.
 */

void afficheGrille(caseGrille **grille, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurLigne(int valeur, caseGrille **grille, int ligne, size_t taille) 
 * \brief La fonction "absentSurLigne" permet de vérifier si la valeur que l'on veut affecter à une case est présente sur la ligne de la case testée.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param ligne - la ligne à tester.
 * \param valeur - la valeur à tester.
 * \return 1 si la valeur est absente de la ligne.
 * \return 0 si la valeur est présente sur la ligne.
*/

int absentSurLigne (uint8_t valeur, caseGrille **grille, size_t ligne, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurColonne(int valeur, caseGrille **grille, int colonne, size_t taille) 
 * \brief La fonction "absentSurColonne" permet de vérifier si la valeur que l'on veut affecter à une case est présente sur la colonne de la case testée.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param colonne - la colonne à tester.
 * \param valeur - la valeur à tester.
 * \return 1 si la valeur est absente de la colonne.
 * \return 0 si la valeur est présente sur la colonne.
*/

int absentSurColonne (uint8_t valeur, caseGrille **grille, size_t colonne, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Charly Maeder
 * \fn int absentSurRegion(int valeur, caseGrille **grille, int ligne, int colonne, size_t taille) 
 * \brief La fonction "absentSurRegion" permet de vérifier si la valeur que l'on veut affecter à une case est présente sur la zone de la case testée.
 * \param grille - la grille.
 * \param taille - la taille de la grille.
 * \param ligne -la ligne à tester.
 * \param colonne - la colonne à tester.
 * \param valeur - la valeur à tester.
 * \return 1 si la valeur est absente de la région.
 * \return 0 si la valeur est présente sur la région.
*/

int absentSurRegion (uint8_t valeur, caseGrille **grille, size_t ligne, size_t colonne, size_t taille);


/**
 * \author Stella Zevio
 * \fn void echange(uint8_t *a, uint8_t *b)
 * \brief La fonction "echange" permet d'échanger deux valeurs.
 * \param a - la première valeur a echanger.
 * \param b - la deuxième valeur a echanger.
*/

void echange(uint8_t *a, uint8_t *b);


/**
 * \author Stella Zevio
 * \fn void melangerTableauValeurs(void)
 * \brief La fonction "melangerTableauValeurs" permet de rendre pseudo-aléatoires les valeurs possibles pour remplir la grille. Elle permet de mélanger les valeurs de notre tableau global de valeurs possibles.
*/

void melangerTableauValeurs(uint8_t *tableauValeurs, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant, Stella Zevio
 * \fn bool genererGrilleComplete(caseGrille **grille, int position, size_t taille) 
 * \brief La fonction "genererGrilleComplete" permet la génération de la grille complète de sudoku par le principe du backtracking (retour sur trace).
 * \param grille - la grille.
 * \param position - la position de la case qui est testée (ligne*colonne).
 * \param taille - la taille de la grille.
 * \return true si la grille est correctement générée.
 * \return false si la grille n'est pas correctement générée.
*/

bool genererGrilleComplete(caseGrille **grille, size_t position, size_t taille, uint8_t *tableauValeurs);


/**
 * \author Stella Zevio
 * \fn void genererGrilleJeu(caseGrille** grille, size_t taille) 
 * \brief La fonction "genererGrilleJeu" permet la génération de la grille de jeu en trouant la grille complète (grille de solution).
 * \param grille - la grille.
 * \param taille - la taille de la grille.
*/

void genererGrilleJeu(caseGrille** grille, size_t taille, uint8_t* tableauValeurs);


/**
 * \author Redoine El Ouasti, Stella Zevio
 * \fn int jouer(caseGrille **grille, size_t taille)
 * \brief La fonction "jouer" permet de modifier les valeurs associées aux cases de grille.
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
 * \return 0 si les grilles sont différentes.
*/

int comparaisonGrilles(caseGrille ** premiereGrille, caseGrille ** deuxiemeGrille, size_t taille);


/**
 * \author Abdoulaye Diallo, Adrien Lamant
 * \fn void sauvegarde(caseGrille** grille, caseGrille** grilleSolution, size_t taille, float temps)
 * \brief La fonction "sauvegarde" permet de sauvegarder une partie.
 * \param grille - la grille de jeu.
 * \param grilleSolution - la solution de la grille de jeu (la grille complète).
 * \param taille - la taille des grilles.
 * \param temps - le temps passe a resoudre le sudoku.
*/

void sauvegarde(caseGrille** grille, caseGrille **grilleSolution, size_t taille, float temps);


/**
 * \author Abdoulaye Diallo, Adrien Lamant
 * \fn bool chargerPartie(size_t taille, caseGrille **grilleSolution, caseGrille **grille, float* temps)
 * \brief La fonction "chargerPartie" permet de charger une partie.
 * \param taille - la taille des grilles.
 * \param grilleSolution - la solution de la grille de jeu (la grille complète).
 * \param grille - la grille de jeu.
 * \param temps - le temps passe a resoudre le sudoku.
 * \return true si la grille est chargeable, false sinon.
*/

bool chargerPartie(size_t taille, caseGrille **grilleSolution, caseGrille **grille, float* temps);


/**
 * \author Pierre Ruffin
 * \fn void reinitialiserPartie (caseGrille **grille, size_t taille)
 * \brief La fonction "reinitialiserPartie" permet de reinitialiser la grille de jeu comme en début de partie.
 * \param grille - la grille a modifier.
 * \param taille - la taille des grilles.
 */

void reinitialiserPartie (caseGrille **grille, size_t taille);


/**
 * \author Redoine El Ouasti, Pierre Ruffin, Stella Zevio
 * \fn void void score(size_t taille, float temps) 
 * \brief La fonction "score" permet de sauvegarder les classements des differentes parties (les meilleurs temps de resolution) selon la taille de la grille.
 * \param taille - la taille des grilles.
 * \param temps - le temps passe a resoudre le sudoku.
*/
/*void score(size_t taille, float temps); */


/**
 * \author Charly Maeder, Pierre Ruffin, Stella Zevio
 * \fn bool estInclus(unsigned short case1, unsigned short case2, size_t taille)
 * \brief La fonction "estInclus" permet de verifier qu'un singleton (une unique valeur possible d'une case) est present ailleurs dans les possibilites des cases contenues dans sa ligne, colonne ou region.
 * \param singleton - le singleton.
 * \param possibilitesCase - l'ensemble des possibilites de la case a tester.
 * \param taille - la taille des grilles.
*/

bool estInclus(uint16_t singleton, uint16_t possibilitesCase, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin, Stella Zevio
 * \fn bool crossHatching(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "crossHatching" permet d'eliminer un singleton des possibilites des autres cases de sa sous-grille.
 * \param sousGrille - la sous-grille a tester.
 * \param taille - la taille des grilles.
*/

bool crossHatching(caseGrille *sousGrille, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn bool loneNumber(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "loneNumber" est une heuristique qui permet transformer une aide en singleton si une de ces valeurs n'est pas présente dans les autres cases.
 * \param sousGrille - la sous-grille a tester.
 * \param taille - la taille des grilles.
 */

bool loneNumber(caseGrille *sousGrille, size_t taille);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn int nbValeurs(unsigned short aide)
 * \brief La fonction "nbValeurs" permet de connaître le nombre de bits à 1 pour un unsigned short représentant le nombre de valeurs d'une liste de possibilités.
 * \param aide - la liste de possibilite a denombrer.
*/
int nbValeurs(unsigned short aide);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn int nbOccurence(caseGrille *sousGrille,int indice, size_t taille)
 * \brief La fonction "nbOccurence" permet de connaître le nombre de fois qu'une liste de possibilités apparait. Si elle n'apparait qu'une fois, cela renvoie 0.
 * \param *sousGrille - l'ensemble de listes de possibilites.
 * \param indice - l'indice de la case qu'on cherche à denombrer.
 * \param taille - la taille des grilles.
*/

int nbOccurence(caseGrille *sousGrille,int indice, size_t taille);


/**
 * \author Simon Galand, Pierre-Louis Latour
 * \fn bool nakedSubset(caseGrille *sousGrille, size_t taille)
 * \brief La fonction "nakedSubset" permet de retirer une liste de possibilite si elle repond au Naked Subset, et de renvoyer un booleen temoignant ou non de l'application de cette regle.
 * \param *sousGrille - l'ensemble des listes de possibilites.
 * \param taille - la taille des grilles.
*/

bool nakedSubset(caseGrille *sousGrille, size_t taille);


/**
 * \author Charly Maeder
 * \fn caseGrille** convertirZoneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);
 * \brief La fonction "convertirZoneEnTableau" permet de une zone de la grille en tableau.
 * \param grille - la grille de jeu.
 * \param ligne - la ligne de la grille où se trouve la case où on veut l'aide.
 * \param colonne - la colonne de la grille où se trouve la case où on veut l'aide.
 * \param taille - la taille de la grille.
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
 */
caseGrille** convertirColonneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn void initAide(caseGrille** grille, size_t taille);
 * \brief La fonction "initAide" permet d'initialiser la grille de l'aide en fonction des valeurs des cases.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 */
void initAide(caseGrille** grille, size_t taille);


/**
 * \author Charly Maeder, Pierre Ruffin
 * \fn void aide(caseGrille** grille, const size_t taille);
 * \brief La fonction "aide" permet de créer l'aide pour l'ensemble de la grille.
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 */
void aide(caseGrille** grille, const size_t taille);


/**
 * \author Pierre Ruffin, Charly Maeder
 * \fn void parcoursGrilleAide(caseGrille** grille, size_t taille, size_t ligne, size_t colonne);
 * \brief La fonction "parcoursGrilleAide" permet d'appliqer les heuristiques sur l'ensemble de la grille;
 * \param grille - la grille de jeu.
 * \param taille - la taille de la grille.
 * \param ligne - la ligne de la case où on veut l'aide.
 * \param colonne - la colonne de la case où on veut l'aide.
 */
void parcoursGrilleAide(caseGrille** grille, size_t taille, size_t ligne, size_t colonne);


void echangeInt(int *a, int *b);

int insererPetiteValeur(int* T, char noms[10][30], int val, char nom[30]);

void demanderNom(char *nom);

void score(int temps, size_t taille);

void reinitialiserTop10(size_t taille);

void afficherTop10(size_t taille);

void recupeGrille(caseGrille**grille, size_t taille);


/**
 * \author Redoine El Ouasti, Stella Zevio
 * \fn void libereGrille(caseGrille** grille, size_t taille);
 * \brief La fonction "libereGrille" permet de libérer en mémoire les grilles allouées dynamiquement.
 * \param grille - la grille a liberer.
 * \param taille - la taille de la grille.
*/

void libereGrille(caseGrille** grille, size_t taille);


#endif
