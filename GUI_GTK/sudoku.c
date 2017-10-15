#include "fonctions.h"

/**
 *\file sudoku.c
 *\brief Sudoku
 *\author Simon Galand, Pierre-Louis Latour, Pierre Ruffin
 *\version 0.2
 *\date 2014-03-26
 *
 * Sudoku en C : résolution des grilles 4x4, 9x9, 16x16 et jeu.
 *
 */


/* ORDRE DE COMPILATION : gcc sudoku.c fonctions.c -lm -ansi -pedantic -Wall -O3 -std=c99 -o sudoku */

int main(int argc, char** argv){
   

    bool nouvellePartie = 0; /* permet de gerer la reinitialisation de la partie */
    do {

    	srand((unsigned int)time(NULL));

	caseGrille **grille=NULL, **grilleSolution=NULL; /* grille de jeu, grille de solution */
	char choix=0; /* initialisation du choix permettant de choisir une option du menu */
	size_t taille=0, position=0, menu=0, valeurBoucle=0, sortie=0; /* initialisation de la taille de la grille, position dans la grille, du menu comportant les differentes fonctionnalites de l'application ainsi que de la valeur de la boucle "tant que" nous permettant de faire tourner le menu et le choix des fonctionnalites de l'application et de la sortie de la fonction jouer */
	char quitter; /* declaration d'un caractere permettant de choisir de quitter la partie ou de continuer apres validation de la grille */
	clock_t t1=0, t2=0; /* initialisation du debut et de la fin de l'enregistrement du temps passe a resoudre le sudoku */
	float temps=0; /* initialisation du temps passe a resoudre le sudoku */
	size_t limiteAide=7; /* l'utilisateur ne poura faire appel a l'aide que 7 fois */

	while(!valeurBoucle){

		printf("\x1B[2J" ); /* cette ligne efface le terminal pour ne plus voir les ordres de compilation */

		do{
		printf(" (");
			COULEUR_BLEU
			printf("1");
			COULEUR_ORIGINE
		printf(")Commencer une partie, (");
			COULEUR_BLEU
			printf("2");
			COULEUR_ORIGINE
		printf(")Charger une partie, (");
			COULEUR_BLEU
			printf("3");
			COULEUR_ORIGINE
		printf(")Quitter. \n\t Veuillez saisir votre choix : \n");
			printf("  >> ");
			COULEUR_BLEU
			choix=fgetc(stdin); /* recupere la saisie de l'utilisateur */
			COULEUR_ORIGINE
			menu=(size_t)choix-48; /* conversion */

			if((menu<1) && (menu>3)) { /* si l'utilisateur a entre une valeur indisponible */
				printf("\n\t Veuillez saisir une option de menu disponible. \n");
			}
		} while((menu<1) && (menu>3)); /* tant que l'utilisateur n'a pas entre une valeur disponible */
		

        	switch(menu){ /*************** PREMIER MENU ***************/

                
		    case 1: /* COMMENCER UNE NOUVELLE PARTIE */
				
			    /* Etape 1 : Interface de menu avec choix taille et initialisation de la grille a 0 pour toutes les cases. */
	        
			    taille=initTaille(); /* initialisation de la taille de la grille de sudoku */
			    printf("  La taille sera : %zu*%zu \n",taille, taille);
	   		    grille=initGrille(taille);  /* initialisation de la grille de jeu */
			    grilleSolution=initGrille(taille); /* initialisation de la grille complete (grille de solution) */
	        
			    /* On cree un tableau contenant toute les valeurs possibles a l'interieur des cases de la grille. Ce tableau est une variable globale. */
			    uint8_t *tableauValeurs = malloc(taille*sizeof(uint8_t));
	
			    /* On melange ce tableau afin de rendre les valeurs possibles pseudo-aleatoires lors de la generation de la grille. */
			    melangerTableauValeurs(tableauValeurs, taille);


			    /* Etape 2 : Remplissage de la grille de jeu et de la grille solution. */
	        
			    genererGrilleComplete(grille,position,taille, tableauValeurs); /* generation aleatoire d'une solution complete de la grille */
	        	
			    for(size_t i=0; i<taille; i++){
					    for(size_t j=0; j<taille; j++){
	               				    grilleSolution[i][j].valeur=grille[i][j].valeur;  /* copie de la solution complete dans grillesSolution */
	            			    }
	        	    }
	        
			    //afficheGrille(grilleSolution, taille); /* affichage de la grille de solution : A COMMENTER POUR UNE SESSION REELLE DE JEU */

	       
			    /* Etape 3 : Des cases sont videes pour generer la grille jouable (generation de la grille de jeu) puis affichage de la grille de jeu */
	        
	  			    genererGrilleJeu(grille, taille, tableauValeurs); /* generation de la grille de jeu de sudoku */
				    free(tableauValeurs); /* liberation du tableau de valeurs possibles pseudo-aleatoires */
				    t1=clock(); /* debut de l'enregistrement du temps passe a resoudre le sudoku */
	   			    afficheGrille(grille,taille); /* affichage de la grille */
				    valeurBoucle=1;				
		    break;
		    

    
		    case 2: /* CHARGER UNE PARTIE */
		        
				taille = 0;
				choix = 0;
				taille=initTaille();
				grille=initGrille(taille);  /* initialisation de la grille de jeu */
				grilleSolution=initGrille(taille); /* initialisation de la grille complete (grille de solution) */
				if(!chargerPartie(taille, grilleSolution, grille, &temps)){ /* chargement */
					COULEUR_ROUGE 
					fprintf(stderr,"Le chargement d'une grille %zu*%zu n'est pas possible. \n", taille, taille);
					FLUSH_COULEUR_ORIGINE
					break;
					//valeurBoucle=1;
				}
				else{
					afficheGrille(grille,taille);
					t1=clock()+temps; /* on continue a enregistrer le temps passe a resoudre le sudoku */
					valeurBoucle=1;
				}
		    break;

		        
		    case 3: /* QUITTER LA PARTIE */
		    	    return 0;				
		    break;
		}
	}

	valeurBoucle=0;


	/* Etape 4 : Jeu et utilisation d'un switch pour jouer, comparaison de la grille de jeu completee a la solution complete pour validation, sauvegarde, quitter */

    	while(!valeurBoucle){

		do{
			printf("\n (");
				COULEUR_BLEU
				printf("1");
				COULEUR_ORIGINE
			printf(")Jouer, (");
				COULEUR_BLEU
				printf("2");
				COULEUR_ORIGINE
			printf(")Aide, (");
				COULEUR_BLEU
				printf("3");
				COULEUR_ORIGINE
			printf(")Verification, (");
				COULEUR_BLEU
				printf("4");
				COULEUR_ORIGINE
			printf(")Sauvegarde, (");
				COULEUR_BLEU
				printf("5");
				COULEUR_ORIGINE
			printf(")Chargement, (");
				COULEUR_BLEU
				printf("6");
				COULEUR_ORIGINE
			printf(")Reinitialisation, (");
				COULEUR_BLEU
				printf("7");
				COULEUR_ORIGINE
			printf(")Nouvelle Partie, (");
				COULEUR_BLEU
				printf("8");
				COULEUR_ORIGINE
			printf(")Quitter. \n\t Veuillez saisir votre choix : \n ");

			printf("  >> ");
			fgetc(stdin); /* vide le buffer */
			COULEUR_BLEU
			choix=fgetc(stdin); /* recupere la saisie de l'utilisateur */
			COULEUR_ORIGINE

			menu=(size_t)choix-48; /* conversion */

			if((menu<1) && (menu>8)) { /* si l'utilisateur a entre une valeur indisponible */
				printf("\n\t Veuillez saisir une option de menu disponible. \n");
			}
		} while((menu<1) && (menu>8)); /* tant que l'utilisateur n'a pas entre une valeur disponible */
        
		switch(menu){ /*************** DEUXIEME MENU ***************/

		    case 1: /* JOUER */

			    while(!sortie){
				    jouer(grille,taille); /* jeu */
                    afficheGrille(grille,taille); /* affichage de la grille de jeu */
					sortie=1;
				}
				sortie=0;
		    break;


		    case 2: /* AIDE */
                
				if(!limiteAide){ /* si la limite est atteinte alors on accede pas a l'aide */
					COULEUR_ROUGE
					fprintf(stderr,"Attention vous avez utilise la totalité de vos aides\n");
					FLUSH_COULEUR_ORIGINE
					break;
				}

				printf("\t Veuillez saisir la ligne de la case dont vous souhaitez afficher les valeurs possibles : \n");
				printf("  >> ");
				COULEUR_BLEU
				fgetc(stdin);
				COULEUR_ORIGINE
				size_t ligne=fgetc(stdin)-48;
				ligne--;

			    printf("\t Veuillez saisir la colonne de la case dont vous souhaitez afficher les valeurs possibles :\n");
				printf("  >> ");
				COULEUR_BLEU
			    fgetc(stdin);
				COULEUR_ORIGINE
			    size_t colonne=fgetc(stdin)-48;
				colonne--;

			    if(grille[ligne][colonne].modifiable==1){

			  	    aide(grille, taille);/* On appelle la fonction aide pour toute la grille qui va creer l'aide de toutes les cases de la grille */
				    printf("\nLes valeurs possibles sont: ");
					for (size_t i = 1; i <= taille; i++) {
						if (!!( grille[ligne][colonne].aide & (1u << (i-1))) == 1)
							printf("%lu ", i);/*On affiche l'aide de la case voulu*/
					}
					printf("\n");
					limiteAide--;
				}	
			    else {
					COULEUR_ROUGE
					fprintf(stderr,"La case choisie n'est pas modifiable\n");
					FLUSH_COULEUR_ORIGINE
				}
				afficheGrille(grille,taille); /* affichage de la grille de jeu */
			break;


		    case 3: /* VERIFICATION (validation de la grille apres comparaison de la grille de jeu completee a la solution complete) */
                
		    	    if (comparaisonGrilles(grille, grilleSolution, taille)){ /* comparaison de la grille de jeu a la solution complete : si elles sont identiques, renvoie vrai */
		            	    printf("\n\t Felicitations, vous avez gagne ! \n");
		            
			    t2=clock(); /* fin de l'enregistrement du temps passe a resoudre le sudoku */
			    temps=(float)(t2-t1)/CLOCKS_PER_SEC; /* calcul du temps passe a resoudre le sudoku */
		            
			    /* VERIFICATION DU SCORE PAS ENCORE IMPLEMENTE */
					
			    printf("\t Voulez vous quitter la partie ? (o/n) : ");
				    do {
							printf("  >> ");
							COULEUR_BLEU
				    	    fgetc(stdin);
							COULEUR_ORIGINE
				    	    quitter = fgetc(stdin);

					    if (quitter=='o'){
						    printf("\t Merci d'avoir joue et a bientot. \n");
						    libereGrille(grille, taille); /* liberation de la grille de jeu */
			    			    libereGrille(grilleSolution, taille); /* liberation de la grille complete */
						    valeurBoucle=1;
					    }
					    else if (quitter=='n'){
						    break;
					    }
					    else {
							COULEUR_ROUGE
						    fprintf(stderr, "Veuillez saisir 'o' pour quitter la partie ou 'n' pour continuer : \n");
							FLUSH_COULEUR_ORIGINE
					    }
				    } while(quitter!='o' && quitter!='n');
			    }
			    else{
					COULEUR_ROUGE 
					fprintf(stderr,"\t La grille n'a pas ete correctement completee. Veuillez continuer ou quitter la partie. \n");
					FLUSH_COULEUR_ORIGINE
				}
			
			break;

		    case 4: /* SAUVEGARDER LA PARTIE */

			    t2=clock(); /* fin de l'enregistrement du temps passe a resoudre le sudoku */
			    temps=(float)(t2-t1)/CLOCKS_PER_SEC; /* calcul du temps passe a resoudre le sudoku */
                
			    sauvegarde(grille, grilleSolution, taille, temps); /* sauvegarde de la partie */
                    break;
                

		    case 5: /* CHARGER LA PARTIE */
					taille=initTaille();
					if(!chargerPartie(taille, grilleSolution, grille, &temps)){ /* chargement d'une grille prealablement sauvegardee */
						COULEUR_ROUGE 
						fprintf(stderr,"Le chargement d'une grille %zu*%zu n'est pas possible. \n", taille, taille);
						FLUSH_COULEUR_ORIGINE
						break;
					}else{
						afficheGrille(grille, taille); /* affichage de la nouvelle grille de jeu */
						t1=clock()+temps; /* on continue a enregistrer le temps passe a resoudre le sudoku */
					}
				break;


		    case 6: /* REINITIALISER LA PARTIE */
                	reinitialiserPartie(grille, taille); /* reinitialisation de la partie */
                	afficheGrille(grille, taille); /* affichage de la grille de jeu */
                break;



		    case 7: /* NOUVELLE PARTIE */
    			    libereGrille(grille, taille); /* liberation de la grille de jeu */
			    	libereGrille(grilleSolution, taille); /* liberation de la grille complete */				
                	nouvellePartie = 1;
                	valeurBoucle = 1;
				break;


		    case 8: /* QUITTER LA PARTIE */
                	printf("\t Merci d'avoir joue et a bientot. \n");
			    	libereGrille(grille, taille); /* liberation de la grille de jeu */
			    	libereGrille(grilleSolution, taille); /* liberation de la grille complete */
                	valeurBoucle=1; /* fin de l'algorithme principal */
				break;
        	}
    	}

    } while(nouvellePartie==1);

    return 0;
}


