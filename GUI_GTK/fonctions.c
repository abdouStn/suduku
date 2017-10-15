/**
 *\file fonctions.c
 *\brief Sudoku
 *\author Abdoulaye Diallo, Redoine El Ouasti, Simon Galand, Adrien Lamant, Pierre-Louis Latour, Charly Maeder, Pierre Ruffin, Stella Zevio
 *\version 0.2
 *\date 2014-03-26
 *
 * Sudoku en C : résolution des grilles 4x4, 9x9, 16x16 et jeu.
 *
 */


#include"fonctions.h"


/* ============ INITIALISATION ============ */

size_t initTaille(){ /* INITIALISE LA TAILLE DE LA GRILLE DE SUDOKU. */

	size_t taille = 0;
	char choix = 0;

	while((choix!=49) && (choix!=50) && (choix!=51)){ /* code ascii de 1, 2, et 3 pour securiser la saisie de la taille */

		printf("\nVeuillez entrer le niveau de difficulte de la grille de jeu\n");

		printf("\n\t(");
			COULEUR_BLEU
			printf("1");
			COULEUR_ORIGINE
		printf(") pour une grille de taille 4*4\n\t(");
			COULEUR_BLEU
			printf("2");
			COULEUR_ORIGINE
		printf(") pour une grille de taille 9*9\n\t(");
			COULEUR_BLEU
			printf("3");
			COULEUR_ORIGINE
		printf(") pour une grille de taille 16*16 \n");

       	printf("  >> ");
		fgetc(stdin); /* saisie de l'utilisateur */
		COULEUR_BLEU
		choix = fgetc(stdin); /* recuperation de la saisie de l'utilisateur */
        COULEUR_ORIGINE

		if((choix!=49) && (choix!=50) && (choix!=51)) {
			printf("\n\t La taille demandee n'est pas disponible. \n");
		}
		if(choix==49)
			taille = (size_t)choix - 48 + 3; /* convertir le choix 49 en taille 4 */
		else if(choix==50)
			taille = (size_t)choix - 48 + 7; /* convertir le choix 50 en taille 9 */
		else if(choix==51)
			taille = (size_t)choix - 48 + 13; /* convertir le choix 51 en taille 16 */
	}
	return taille;
}



caseGrille** initGrille(size_t taille){ /* INITIALISE LA GRILLE DE SUDOKU. */

	size_t ligne;
	size_t colonne;
	caseGrille **grille;

	/* Allocation dynamique de la grille */

	grille=malloc(taille*sizeof(caseGrille*)); /* allocation de la premiere dimension de la grille */

	if(grille==NULL){ /* si l'allocation de la premiere dimension de la grille a echoue */
		COULEUR_ROUGE
		fprintf(stderr, "Erreur lors de l'allocation de la grille (premiere dimension)\n");
		FLUSH_COULEUR_ORIGINE
		exit(-1);
	}

	for(ligne=0;ligne<taille;ligne++){
		grille[ligne]=calloc(taille,sizeof(caseGrille)); /* allocation de la deuxieme dimension de la grille */
			if(grille[ligne]==NULL){ /* si l'allocation de la deuxieme dimension de la grille a echoue */
				/* Liberation de la grille */
				for(ligne=ligne-1;ligne>=0;ligne--){
					free(grille[ligne]); /* liberation de la deuxieme dimension de la grille */
				}
				free(grille); /* liberation de la premiere dimension de la grille */
				COULEUR_ROUGE
				fprintf(stderr, "Erreur lors de l'allocation de la grille (deuxieme dimension)\n");
				FLUSH_COULEUR_ORIGINE
				exit(-2);
			}
	}

	for(ligne=0; ligne<taille; ligne++){
		for(colonne=0; colonne<taille; colonne++){
			grille[ligne][colonne].valeur=0; /* chaque case prend pour valeur 0 */
			grille[ligne][colonne].modifiable=1; /* chaque case est modifiable */
			grille[ligne][colonne].aide=0xFFFF; /* initialisation de l'aide, toute les valeurs sont possibles */
		}
	}
	return grille;
}



/* ============ AFFICHAGE ============ */

void afficheGrille(caseGrille **grille, size_t taille){ /* AFFICHE LA GRILLE DE SUDOKU. */
	printf("\n"); /* saut de ligne initial pour afficher la grille */
	size_t ligne,colonne;

	/* GRILLE 4*4 */
	if(taille==4){
		for (ligne=0; ligne<2*taille+3;ligne++){
            		printf("-"); /* affichage d'une separation */
		}
		printf("\n"); /* saut de ligne */

		for (ligne=0; ligne<taille; ligne++){
			for (colonne=0; colonne<taille; colonne++){
						if(grille[ligne][colonne].modifiable==0)
							COULEUR_VERTE
							printf( "%d ", grille[ligne][colonne].valeur);
							COULEUR_ORIGINE
							if(!((colonne+1)%((size_t)sqrt(taille))))
                		 		printf("| "); /* affichage de la valeur, ou de la valeur et d'un separateur */
			}
			putchar('\n'); /* saut de ligne */

			if (!((ligne+1)%(((size_t)sqrt(taille))))){
       			size_t ligne=0;
        		for (ligne=0; ligne<2*taille+3;ligne++){
            			printf("-"); /* affichage d'une separation */
        		}
        		printf("\n");
			}
		}
		puts("\n");
	}

	/* GRILLE 9*9 */
	else if(taille==9){
		for (ligne=0; ligne<2*taille+5;ligne++){
            		printf("-"); /* affichage d'une separation */
		}

		printf("\n"); /* saut de ligne */

		for (ligne=0; ligne<taille; ligne++){
			for (colonne=0; colonne<taille; colonne++){
				if(grille[ligne][colonne].modifiable==0)
					COULEUR_VERTE
					printf( "%d ", grille[ligne][colonne].valeur);
					COULEUR_ORIGINE
					if(!((colonne+1)%((size_t)sqrt(taille))))
        		 		printf("| "); /* affichage de la valeur, ou de la valeur et d'un separateur */
			}
			putchar('\n'); /* saut de ligne */
			if (!((ligne+1)%(((size_t)sqrt(taille))))){
       			size_t ligne=0;
        		for (ligne=0; ligne<2*taille+5;ligne++){
            			printf("-"); /* affichage d'une separation */
        		}
        		printf("\n");
			}
        }
		puts("\n");
	}

	/* GRILLE 16*16 */
	else {
		for (ligne=0; ligne<3*taille+7;ligne++){
            		printf("-"); /* affichage d'une separation */
		}
		printf("\n"); /* saut de ligne */
		for (ligne=0; ligne<taille; ligne++){
			for (colonne=0; colonne<taille; colonne++){
				if (grille[ligne][colonne].valeur<10){
					if(grille[ligne][colonne].modifiable==0)
						COULEUR_VERTE
						printf( " %d ", grille[ligne][colonne].valeur);
						COULEUR_ORIGINE
						if(!((colonne+1)%((size_t)sqrt(taille))))
            		 		printf("| "); /* affichage de la valeur, ou de la valeur et d'un separateur */
				}
				else {
					if(grille[ligne][colonne].modifiable==0)
						COULEUR_VERTE
						printf( "%d ", grille[ligne][colonne].valeur);
						COULEUR_ORIGINE
						if(!((colonne+1)%((size_t)sqrt(taille))))
            		 		printf("| "); /* affichage de la valeur, ou de la valeur et d'un separateur */
				}
			}
			putchar('\n'); /* saut de ligne */
			if (!((ligne+1)%(((size_t)sqrt(taille))))){
        		size_t ligne=0;
        		for (ligne=0; ligne<3*taille+7;ligne++){
            			printf("-"); /* affichage d'une separation */
        		}
        		printf("\n");
			}
        }
		puts("\n");
	}
}



/* ============ CONDITIONS DE VALIDITE  ============ */

int absentSurLigne (uint8_t valeur, caseGrille **grille, size_t ligne, size_t taille){ /* VERIFIE SI LA VALEUR QUE L'ON VEUT AFFECTER A LA CASE EST DEJA PRESENTE SUR LA LIGNE */
	size_t colonne;
	for (colonne=0; colonne < taille; colonne++)
		if (grille[ligne][colonne].valeur == valeur) /* si la valeur est presente sur la ligne */
			return 0;
	return 1;
}



int absentSurColonne (uint8_t valeur, caseGrille **grille, size_t colonne, size_t taille){ /* VERIFIE SI LA VALEUR QUE L'ON VEUT AFFECTER A LA CASE EST DEJA PRESENTE SUR LA COLONNE */
	size_t ligne;
	for (ligne=0; ligne < taille; ligne++)
		if (grille[ligne][colonne].valeur == valeur) /* si la valeur est presente sur la colonne */
			return 0;
	return 1;
}



int absentSurRegion (uint8_t valeur, caseGrille **grille, size_t ligne, size_t colonne, size_t taille){ /* VERIFIE SI LA VALEUR QUE L'ON VEUT AFFECTER A LA CASE EST DEJA PRESENTE SUR LA REGION */
	size_t i = ligne-(ligne%(size_t)sqrt(taille)), j = colonne-(colonne%(size_t)sqrt(taille));  /* ou encore : i = 3*(ligne/3), j = 3*(colonne/3); */
	for (ligne=i; ligne < i+sqrt(taille); ligne++)
		for (colonne=j; colonne < j+sqrt(taille); colonne++)
			if (grille[ligne][colonne].valeur == valeur) /* si la valeur est presente sur la region */
				return 0;
	return 1;
}



void echange(uint8_t *a, uint8_t *b){ /* PERMET D'ECHANGER DEUX VALEURS */
	uint8_t c=*a;
	*a=*b;
	*b=c;
}


/* ============ GENERATION DE LA GRILLE COMPLETE (SOLUTION) ============ */


void melangerTableauValeurs(uint8_t* tableauValeurs, size_t taille){ /* REND LES VALEURS POSSIBLES DES CASES DE LA GRILLE PSEUDO-ALEATOIRES */
	for(size_t i=0; i<taille; i++)
		tableauValeurs[i] = i+1;

	/* On melange les valeurs du tableau. */
	for(size_t i=0; i<taille; i++)
		echange(&tableauValeurs[i], &tableauValeurs[rand()%taille]);
}


bool genererGrilleComplete(caseGrille **grille, size_t position, size_t taille, uint8_t * tableauValeurs){ /* GENERATION DE LA GRILLE COMPLETE (SOLUTION) */
	if (position == taille*taille) /* 81,16,256 (derniere case de taille 9,4,16) */
		return true; /* On sort de la boucle si on est arrivé a la derniere case */

	size_t ligne;
	ligne=(position/taille);
	size_t colonne = position%taille; /* On initialise la position de la premiere case en fonction de la ligne et de la colonne */

	if(grille[ligne][colonne].valeur!=0){ /* si la valeur ne contient pas de 0 */
		return genererGrilleComplete(grille, position+1, taille, tableauValeurs); /* c'est qu'elle est deja correcte */
	}

	for(size_t i=0; i<taille; i++){
		if(absentSurLigne(tableauValeurs[i],grille,ligne, colonne) && absentSurColonne(tableauValeurs[i],grille,colonne, ligne) && absentSurRegion(tableauValeurs[i],grille,ligne,colonne, taille)){ /* verification des conditions de validite */
			grille[ligne][colonne].valeur = tableauValeurs[i]; /* on affecte la valeur a la grille temporaire */
			if(genererGrilleComplete(grille, position+1, taille, tableauValeurs)){ /* si la position suivante est correcte */
				return true;
			}
		}
	}

	grille[ligne][colonne].valeur = 0; /* sinon on efface la valeur */
	return false;
}



/* ============ GENERATION DE LA GRILLE VIDEE (JEU) ============ */

void genererGrilleJeu(caseGrille** grille, size_t taille, uint8_t* tableauValeurs){ /* GENERATION DE LA GRILLE DE JEU (CASES VIDEES) A PARTIR DE LA GRILLE COMPLETE (SOLUTION) */
	size_t casesModifiables, casesVides, ligne, colonne, l, c, i;
	uint8_t temp, valeur;
	caseGrille**grilleTemp;
	bool unique;
	int cpt;
	size_t rdm;

	casesModifiables=taille*taille; /* on initialise le nombre de cases modifiables */
	casesVides=0; /* on initialise le nombre de cases qu'on a reussi a vider */
	grilleTemp=initGrille(taille); /* on initialise une grille temporaire */
	uint8_t *tabLigne=malloc(taille*taille*sizeof(uint8_t)); /* on stockera tous les indices de lignes de la grille dans un tableau */
	uint8_t *tabColonne=malloc(taille*taille*sizeof(uint8_t)); /* on stockera tous les indices de colonnes de la grille dans un tableau */
	cpt=0; /* compteur permettant de compter les indices par groupes de taille */
	rdm=0; /* iterateur des indices de lignes et de colonnes dans les tableaux permettant une pseudo randomisation des indices */

	for(i=0; i<taille*taille; i++){ /* pour toutes les cases */
		if(cpt==taille){ /* si le compteur a atteint la fin d'un groupe de taille */
			cpt=0; /* on remet le compteur a zero */
		}
		tabLigne[i]=cpt; /* la valeur de l'indice dans le tableau de lignes est celle du compteur */
		tabColonne[i]=cpt; /* la valeur de l'indice dans le tableau de colonnes est celle du compteur */
		cpt++; /* on incremente la valeur du compteur */
	}

	for(i=0; i<taille*taille; i++){ /* pour toutes les cases */
		ligne=rand()%taille+i-1; /* on choisit une ligne au hasard */
		echange(&tabLigne[i], &tabLigne[ligne]); /* on melange les valeurs des indices de ligne */
	}

	for(i=0; i<taille*taille; i++){ /* pour toutes les cases */
		colonne=rand()%taille+i-1; /* on choisit une colonne au hasard */
		echange(&tabColonne[i], &tabColonne[colonne]); /* on melange les valeurs des indices de colonne */
	}

	if(taille==4 || taille==9){
		while(rdm<casesModifiables){ /* tant qu'il existe des cases encore modifiables */
			ligne=tabLigne[rdm]; /* on choisit une ligne au hasard */
			colonne=tabColonne[rdm]; /* on choisit une colonne au hasard */

			temp=grille[ligne][colonne].valeur; /* on recupere la valeur initiale de la case */

			for(l=0;l<taille;l++){
				for(c=0;c<taille;c++){ /* pour toutes les valeurs */
					grilleTemp[l][c].valeur=grille[l][c].valeur; /* on copie les valeurs de la grille en l'etat actuel dans une grille temporaire */
					grilleTemp[l][c].modifiable=grille[l][c].modifiable; /* on copie l'etat des cases de la grille en l'etat actuel dans une grille temporaire */
				}
			}

			unique=true; /* la grille a une solution unique */

			grille[ligne][colonne].valeur=0;

			for(valeur=1; valeur<taille+1; valeur++){ /* pour toutes les valeurs possibles */

					if(valeur!=temp && absentSurLigne(valeur, grilleTemp, ligne, taille) && absentSurColonne(valeur, grilleTemp, colonne, taille) && absentSurRegion(valeur, grilleTemp, ligne, colonne, taille)){ /* differentes de la valeur initiale et absentes de la ligne, colonne et region de la case */
						grilleTemp[ligne][colonne].valeur=valeur; /* on affecte cette valeur a la case de la grille temporaire */

						if(genererGrilleComplete(grilleTemp, 0, taille, tableauValeurs)){ /* si on arrive a generer une grille complete avec une valeur differente de la valeur initiale */
							unique=false; /* la grille n'a pas de solution unique */
							break;
						}
					}
			}

			if(!unique){ /* si la grille n'a plus de solution unique */
				grille[ligne][colonne].valeur=temp; /* on remet la valeur initiale de la case */
				grille[ligne][colonne].modifiable=0; /* la case est necessaire, donc non modifiable */
			}

			else {
				casesVides++; /* le ss vides augmente */
			}

			rdm++; /* on passe a la case suivante */


		}
		//free(tabLigne);
		//free(tabColonne);
	}

	if(taille==16) { /* APPROXIMATION POUR LA 16*16 POUR CAUSE DE COMPLEXITE TROP IMPORTANTE */
		while(casesVides<50){ /* tant qu'on peut encore vider des cases sans que la complexite ne soit trop importante */
			ligne=tabLigne[rdm]; /* on choisit une ligne au hasard */
			colonne=tabColonne[rdm]; /* on choisit une colonne au hasard */

			temp=grille[ligne][colonne].valeur; /* on recupere la valeur initiale de la case */

			for(l=0;l<taille;l++){
				for(c=0;c<taille;c++){ /* pour toutes les valeurs */
					grilleTemp[l][c].valeur=grille[l][c].valeur; /* on copie les valeurs de la grille en l'etat actuel dans une grille temporaire */
					grilleTemp[l][c].modifiable=grille[l][c].modifiable; /* on copie l'etat des cases de la grille en l'etat actuel dans une grille temporaire */
				}
			}

			unique=true; /* la grille a une solution unique */

			grille[ligne][colonne].valeur=0;

			for(valeur=1; valeur<taille+1; valeur++){ /* pour toutes les valeurs possibles */

					if(valeur!=temp && absentSurLigne(valeur, grilleTemp, ligne, taille) && absentSurColonne(valeur, grilleTemp, colonne, taille) && absentSurRegion(valeur, grilleTemp, ligne, colonne, taille)){ /* differentes de la valeur initiale et absentes de la ligne, colonne et region de la case */
						grilleTemp[ligne][colonne].valeur=valeur; /* on affecte cette valeur a la case de la grille temporaire */

						if(genererGrilleComplete(grilleTemp, 0, taille, tableauValeurs)){ /* si on arrive a generer une grille complete avec une valeur differente de la valeur initiale */
							unique=false; /* la grille n'a pas de solution unique */
							break;
						}
					}
			}

			if(!unique){ /* si la grille n'a plus de solution unique */
				grille[ligne][colonne].valeur=temp; /* on remet la valeur initiale de la case */
				grille[ligne][colonne].modifiable=0; /* la case est necessaire, donc non modifiable */
			}

			else {
				casesVides++; /* le nombre de cases vides augmente */
			}

			rdm++; /* on passe a la case suivante */
		}
	}



	printf("  nombre de cases vides : %zu \n", casesVides);

	for(i=0; i<taille; i++){
		for(size_t j=0; j<taille; j++){
			if(grille[i][j].valeur==0){
				grille[i][j].modifiable=1;
			}
			else {
				grille[i][j].modifiable=0;
			}
		}
	}
	free(tabLigne);
	free(tabColonne);
	libereGrille(grilleTemp, taille); /* liberation de la grille temporaire */
}



/* ============ JOUER ============ */

void jouer(caseGrille **grille, size_t taille){ /* PERMET A L'UTILISATEUR DE JOUER, EN MODIFIANT LES VALEURS DES CASES DE GRILLE SOUHAITEES */
	size_t ligne;
	size_t colonne;
	uint8_t valeur;

	do {
		printf("Veuillez saisir la ligne de la case dont vous souhaitez modifier la valeur : \n");
		printf("  >> ");
		fgetc(stdin);
		ligne=(size_t)fgetc(stdin)-48;
	} while(ligne>taille || ligne<=0); /* tant que la valeur entree pour l'indice de la ligne ne satisfait pas les conditions de validite */

	ligne--; /* correction de l'indice de la ligne. L'utilisateur entre la 'valeur algorithmique' de l'indice, de 1 a la taille de la grille, nous utilisons la 'valeur en programmation' de l'indice de 0 a taille-1 */

	do {
		printf("Veuillez saisir la colonne de la case dont vous souhaitez modifier la valeur : \n");
		printf("  >> ");
		fgetc(stdin);
		colonne=(size_t)fgetc(stdin)-48;
	} while(colonne>taille || colonne <=0); /* tant que la valeur entree pour l'indice de la ligne ne satisfait pas les conditions de validite */

	colonne--; /* correction de l'indice de la colonne. L'utilisateur entre la 'valeur algorithmique' de l'indice, de 1 a la taille de la grille, nous utilisons la 'valeur en programmation' de l'indice de 0 a taille-1 */

	if (colonne < taille && colonne >= 0 && ligne < taille && ligne >= 0 && grille[ligne][colonne].modifiable !=0){ /* si les indices de ligne et colonne entres sont valides et que la case est modifiable */
		do {
			printf("Veuillez saisir la valeur que vous souhaitez affecter : \n");
			printf("  >> ");
			fgetc(stdin);
			valeur=(uint8_t)fgetc(stdin)-48;
			if((valeur>taille) || (valeur<=0)){ /* si la valeur ne satisfait pas les conditions de validite */
				COULEUR_ROUGE
				fprintf(stderr,"La valeur ne satisfait pas les conditions de validite.\n Veuillez saisir une valeur comprise entre 1 et %zu\n", taille); /* affichage d'un message d'erreur */
				FLUSH_COULEUR_ORIGINE
			}
		} while((valeur>taille) || (valeur<= 0));  /* tant que la valeur entree ne satisfait pas les conditions de validite */

		if(grille[ligne][colonne].valeur==0) /* si aucune valeur n'etait affectee a la case */
			grille[ligne][colonne].valeur=valeur; /* on affecte la valeur saisie a cette case */
		else {
			char choix; /* sinon verification avant d'ecraser une valeur precedemment affectee  */
			do{
				printf("Une valeur a deja ete affectee a cette case. Voulez vous la modifier ? (o/n) \n");
				printf("  >> ");
				fgetc(stdin);  /* pour vider le buffer */
				COULEUR_BLEU
				choix = fgetc(stdin);
				COULEUR_ORIGINE
				if(choix=='o')
					grille[ligne][colonne].valeur=valeur; /* modification de la valeur*/
				else if(choix=='n')
					break; /* sinon on annule */
				else{
					COULEUR_ROUGE
					fprintf(stderr,"Veuillez saisir o pour modifier la case, n pour annuler\n"); /* si l'utilisateur s'est trompe, on lui redemande */
					FLUSH_COULEUR_ORIGINE
				}
			} while(choix != 'o' && choix != 'n'); /* tant que le choix n'est pas effectue */

		}
	}

	else {
		COULEUR_ROUGE
		fprintf(stderr,"La case choisie n'est pas modifiable\n");
		FLUSH_COULEUR_ORIGINE
	}
}



/* ============ SAUVEGARDE, CHARGEMENT, REINITIALISATION ET VALIDATION DE LA PARTIE ============ */

void sauvegarde(caseGrille** grille, caseGrille **grilleSolution, size_t taille, float temps){ /* SAUVEGARDE DE LA GRILLE DE JEU ET DE SA SOLUTION */
	FILE* fichier = NULL; /* initialisation d'un fichier */
	if (taille==4)
		fichier = fopen("sudo4.bin", "wb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */
	else if (taille==9)
		fichier = fopen("sudo9.bin", "wb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */
	else if (taille==16)
		fichier = fopen("sudo16.bin", "wb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */
	if (fichier != NULL){
		//fwrite(&taille, sizeof(size_t), 1, fichier);  /* sauvegarde de la taille de la grille */
		int i;
		int j;
		for (i=0;i<taille;i++){
			for(j=0;j<taille;j++){
				fwrite(&grilleSolution[i][j].valeur,sizeof(int),1,fichier);// CHANGEMENT
			}
		}

		//fputc('\n',fichier);
   	    	for (i=0;i<taille;i++){
			for(j=0;j<taille;j++){
				fwrite(&grille[i][j].valeur,sizeof(int),1,fichier); /* sauvegarde des valeurs des cases */
				fwrite(&grille[i][j].modifiable,sizeof(int),1,fichier); /* sauvegarde de l'etat de la case : modifiable ou fixee par la generation de la grille de jeu */
			}
		}
		//fputc('\n',fichier);
		fwrite(&temps,sizeof(float),1,fichier); /* sauvegarde du temps passe a resoudre le sudoku */
		printf("\n\t La partie a ete sauvegardee \n");
   	}
   	else{
			COULEUR_ROUGE
    		fprintf(stderr, "Impossible d'ouvrir le fichier sudoku_sauvegarde.txt\n"); /* sinon on affiche un message d'erreur */
			FLUSH_COULEUR_ORIGINE
    	}
	fclose(fichier); /* fermeture du fichier */
}


bool chargerPartie(size_t taille, caseGrille **grilleSolution, caseGrille **grille, float* temps){ /* CHARGEMENT D'UNE GRILLE PREALABLEMENT SAUVEGARDEE */

	FILE* fichier = NULL;

	bool chargeable=true;

	if (taille==4)
		fichier = fopen("sudo4.bin", "rb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */
	else if (taille==9)
		fichier = fopen("sudo9.bin", "rb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */
	else if (taille==16)
		fichier = fopen("sudo16.bin", "rb"); /* ouverture du fichier sudoku_sauvegarde.txt en ecriture binaire */

	if (fichier != NULL){
		int i=0;
		int j=0;

		for(i=0;i<taille;i++){
			for (j=0; j<taille; j++){

		  		fread(&grilleSolution[i][j].valeur, sizeof(int), 1, fichier);
		  	}
		}

		for(i=0;i<taille;i++){
			for (j=0; j<taille; j++){
		  		fread(&grille[i][j].valeur, sizeof(int), 1, fichier);
				fread(&grille[i][j].modifiable, sizeof(int), 1, fichier);
			}
		}

		fread(temps, sizeof(float), 1, fichier);

		printf("\nle temps est : %f\n", *temps);
		fclose(fichier);
	}
	else {
		chargeable=false;
		COULEUR_ROUGE
		fprintf(stderr, "le fichier n'a pas été ouvert\n");
		FLUSH_COULEUR_ORIGINE
	}
	return chargeable;
}



void reinitialiserPartie(caseGrille **grille, size_t taille){ /* REINITIALISATION DE LA PARTIE */
	for (size_t ligne = 0; ligne < taille; ligne++) {
		for (size_t colonne = 0; colonne < taille; colonne++) {
			if (grille[ligne][colonne].modifiable==1) /* si la case etait modifiable */
				grille[ligne][colonne].valeur = 0; /* on remet sa valeur a zero */
		}
	}
	printf("La partie a ete reinitialisee\n");
}



int comparaisonGrilles(caseGrille ** premiereGrille, caseGrille ** deuxiemeGrille, size_t taille){ /* COMPARAISON DE DEUX GRILLES DE SUDOKU POUR VALIDATION */
	size_t ligne,colonne;

	for(ligne=0;ligne<taille;ligne++){
		for(colonne=0;colonne<taille;colonne++){
			if(premiereGrille[ligne][colonne].valeur!=deuxiemeGrille[ligne][colonne].valeur){ /* si les grilles ont des valeurs differentes */
				return 0;
			}
		}
	}
	return 1;
}



/* ============ HEURISTIQUES ============ */

bool estInclus(uint16_t singleton, uint16_t possibilitesCase, size_t taille){
	for(size_t i = 0; i< 16; i++) /* pour tous les bits servant a modeliser les valeurs possibles de la case */
		if(!!(singleton & (1u << i)) && !!(possibilitesCase & (1u << i))) /* si le singleton qu'on veut tester est inclus dans l'ensemble des possibilites d'une case de la ligne ou colonne ou region */
			return true; /* alors vrai */
	return false;
}



bool crossHatching(caseGrille *sousGrille, size_t taille){
	bool present = false; /* variable testant la presence d'une unique possibilite de valeur associee a la case */

	for(size_t i=0; i<taille; i++) /* sur l'ensemble de la sous-grille consideree */
		if ((sousGrille[i].aide > 0) && !(sousGrille[i].aide & (sousGrille[i].aide-1))) /* s'il y a un singleton */
			for(size_t j=0; j<taille; j++) /* sur l'ensemble de la sous-grille consideree */
				if(i!=j && estInclus(sousGrille[i].aide, sousGrille[j].aide, taille)){ /* si une des cases de la sous-grille est differente de la case contenant le singleton et si le singleton est inclus dans cette case */
					sousGrille[j].aide =sousGrille[i].aide^sousGrille[j].aide; /* on enleve le singleton de cette case */
					present = true; /* le singleton etant present */
				}
	return present;
}



bool loneNumber(caseGrille* sousGrille, size_t taille) {
	bool present = false;
	size_t j;
	size_t cpt = 0, pst = 0; /*chgmt : variable pour vérifier si il n'y a pas un nouveau loneNumber à effectuer et qui se serait créé après avoir éxecuté l'algorithme
                                                        pst : variable qui donne la position de la case du lone-number
                                                        cpt : compteur
                                                        */

        for (size_t i = 0; i < taille; i++) { /*On parcourt tous les 0 ou 1 qui compose le bit */
		j = 0; cpt = 0;
		while (j < taille && cpt < 2) { /*On parcourt toutes les cases */
			if ((!!(sousGrille[j].aide & (1u<<i))) == 1) { /* On compte le nombre de 1 qu'il y a pour la (((position du bit) du nombre) de l'aide) pour chaque case */
				cpt++;
				pst = j; /*On récupère la position du lone-number */
			}
                j++;
		}
		if (cpt == 1) {
		        sousGrille[pst].aide = (1u << i);
		        present = true;
		}
        }

	return present;
}



int nbValeurs(unsigned short aide){ /* NOMBRE DE POSSIBILITES D'UNE CASE */
	int cpt=0;  /* variable qui sert de compteur */
	for(int i=0; i<16; i++){ /* pour chaque bit */
    		if(!!(aide & (1u<<i))==1){   /* si il y a bien une valeur */
        		cpt++;  /* incrementation du compteur */
        	}
	}
	return cpt; /* on retourne le compteur, qui indique le nombre de valeurs */
}



int nbOccurence(caseGrille *sousGrille,int indice, size_t taille){ /* SI LA POSSIBILITE APPARAIT PLUSIEURS FOIS AU SEIN D'UNE SOUS-GRILLE, ON RENVOIE LE NOMBRE D'OCCURRENCES, SINON 0 */
	size_t i=0; /* indice de parcours */
	int cpt=0;  /* compteur de occurences */
	for(i=0; i<taille; i++){ /* on boucle sur chaque caseGrille de *sousGrille */
        	if((sousGrille[i].aide==sousGrille[indice].aide)&&(i!=indice)){ /* si on retrouve deux valeurs similaires entre i et l'indice */
			cpt++;  /* on incremente le compteur */
		}
	}
	if (cpt!=0){ /* si on a eu une ou des repetitions */
		cpt++;  /* on ajoute 1 pour passer du nombre de repetitions au nombre d'occurences */
	}
	return cpt; /* on retourne le compteur du nombre d'occurences */
}



bool nakedSubset(caseGrille *sousGrille, size_t taille){
	bool b=false;   /* booleen qui permet de savoir si on a fait appel au Naked Subset ou non */
	int i=0;    /* indice de la liste de possibilitees que l'on cherche à enlever si elle apparait autant de fois que sa longueur */
	for(i=0;i<taille;i++){ /*on boucle sur i<taille pour tester toutes les valeurs */
        	if(nbValeurs(sousGrille[i].aide)==(nbOccurence(sousGrille,i,taille))){ /* si la longueur est egale au nombre d'occurences */
			b=true; /* On fait appel au Naked Subset */
			for(int j=0; j<taille; j++){ /* On boucle sur toutes les autres cases */
				if(sousGrille[i].aide!=sousGrille[j].aide){ /* on verifie que ce n'est pas la meme case et que la liste que l'on cherche a enlever est bien presente dans la liste courante */
                    			for(int k=0;k<taille;k++){   /* on boucle sur toutes les valeurs possibles */
                        			if(!!(sousGrille[i].aide&(1u<<k))&&(sousGrille[j].aide&(1u<<k))){   /* si on retrouve une valeur que l'on souhaite enlever a l'incide k */
                            				sousGrille[j].aide=sousGrille[j].aide&~(1u<<k); /* on applique un masque pour la retirer (a l'indice k) */
                        			}
                    			}
                		}
            		}
        	}
    	}
    	return b;   /* On renvoie le booleen qui nous dit si on a utilise le Naked Subset */
}


caseGrille** convertirZoneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille) {
	size_t i = ligne-(ligne%(size_t)sqrt(taille)); /* bornes des boucles en fonction de la ligne et de la colonne de la case donnee : i la bornes pour la ligne et j la borne pour la colonne*/
	size_t j = colonne-(colonne%(size_t)sqrt(taille));
	caseGrille** tabZone = malloc(taille*sizeof(caseGrille*));
	size_t cpt = 0;

	for (ligne = i; ligne < i+sqrt(taille); ligne++) {
		for (colonne = j; colonne < j+sqrt(taille); colonne++) {
			tabZone[cpt] = &grille[i][j]; /*Je recopie l'adresse des cases de la zone dans le tableau tabZone*/
			cpt++;
		}
	}
	return tabZone; /*On renvoie le tableau qui contient les pointeurs des cases de la zone de la grille*/
}


caseGrille** convertirColonneEnTableau(caseGrille** grille, size_t ligne, size_t colonne, size_t taille){
	caseGrille** tabColonne = malloc(taille*sizeof(caseGrille*));
	for (size_t i = 0; i < taille; i++) /*On parcourt toutes les lignes de la colonne et on rentre les adresse de chaques cases dans le tableau tabColonne*/
		tabColonne[i] = &grille[i][colonne];
	return tabColonne;/*On renvoie le tableau tabColonne qui contient l'adresse de toutes les cases de la colonne voulu*/
}


void initAide(caseGrille** grille, size_t taille) {
	for (size_t i = 0; i < taille; i++) {
		for (size_t j = 0; j < taille; j++) {
			if (grille[i][j].valeur != 0) {
				grille[i][j].aide = (1u << (grille[i][j].valeur - 1));/*Si il y a une valeur dans la case, on initialise l'aide de cette case : la seule valeur possible c'est celle qu'il y a déjà*/
			}
			else { /*On initialise l'aide des autres cases avec que des 1*/
				if (taille == 4) grille[i][j].aide = 0x000F;
				else if (taille == 9) grille[i][j].aide = 0x01FF;
				else grille[i][j].aide = 0xFFFF;
			}
		}
	}
}


void aide(caseGrille** grille, const size_t taille) {
	initAide(grille, taille); /*On initialise l'aide de la grille*/

	for (size_t i = 1; i <= taille; i++) {
		for (size_t ligne = 0; ligne < taille; ligne++) {
			for (size_t colonne = 0; colonne < taille; colonne++) {
				if (grille[ligne][colonne].valeur == 0) {
					if ((absentSurLigne(i, grille, ligne, taille) == 0) || (absentSurColonne(i, grille, colonne, taille) == 0) || (absentSurRegion(i, grille, ligne, colonne, taille)) == 0) {
						grille[ligne][colonne].aide &= ~(1u << (i-1)); /*Si une valeur est présente dans la ligne, zone ou colonne alors on met un 0 comme aide pour cette valeur*/
					}
				}
			}
		}
	}

	for (size_t i = 0; i < taille; i++) {
		for (size_t j = 0; j < taille; j++) {
			parcoursGrilleAide(grille, taille, i, j); /*On parcourt l'aide de toute la grille pour appliquer toutes les heuristiques et faire gagner l'aide en précision*/
		}
	}
}


void parcoursGrilleAide(caseGrille** grille, size_t taille, size_t ligne, size_t colonne) {

	caseGrille *tabLigne, *tabColonne, *tabZone;

	tabLigne = malloc(sizeof(taille*sizeof(caseGrille)));
	tabColonne = malloc(sizeof(taille*sizeof(caseGrille)));
	tabZone = malloc(sizeof(taille*sizeof(caseGrille)));
	for (size_t i = 0; i < taille; i++) {
		for (size_t j = 0; j < taille; j++) { /*On parcourt toutes les cases de la grille pour appliquer les heuristiques*/
			tabColonne = *convertirColonneEnTableau(grille, i, j, taille);
			tabZone = *convertirZoneEnTableau(grille, i, j, taille);
			tabLigne = grille[i];
            /*On convertit chaque zone, ligne et colonne de la case choisie en tableau pour appliquer les heuristiques par la suite. */
            loneNumber(tabLigne, taille);
			loneNumber(tabColonne, taille);
			loneNumber(tabZone, taille);
			crossHatching(tabLigne, taille);
			crossHatching(tabColonne, taille);
			crossHatching(tabZone, taille);
			nakedSubset(tabLigne, taille);
			nakedSubset(tabColonne, taille);
			nakedSubset(tabZone, taille);
        	}
	}
}


/* ============ CLASSEMENT (SCORES) ============ */


void echangeInt(int *a, int *b){ /* PERMET D'ECHANGER DEUX VALEURS */
	int c=*a;
	*a=*b;
	*b=c;
}


int insererPetiteValeur(int* T, char noms[10][30], int val, char nom[30]){ /* RETOURNE LA POSITION DE LA VALEUR A MODIFIER, -1 S'IL N'Y EN A PAS */
	char nom_t[30]={""};
	int trouve=-1;
	for(size_t i=0; i<10; i++){
		if(T[i]>val || T[i]==0){
			if(trouve==-1) trouve=i;
			echangeInt(&T[i], &val);

			strcat(nom_t, noms[i]);
			strcat(noms[i], nom);
			strcat(nom, nom_t);
			for(size_t j=0; i<30; i++)
				nom_t[j]='\0';
		}
	}
	return trouve;
}


void demanderNom(char *nom){
	printf("Felicitations, vous avez realise un nouveau score\n");
	printf("Entrez votre pseudo pour enregistrer votre score dans le classement\n");
	printf("  >> ");
	scanf("%s", nom);
}


void score(int temps, size_t taille){
	/*On recupere le nom du fichier*/
	char* nomFichier="";
	if(taille==4)
		nomFichier="top10_4.txt";
	else if(taille==9)
		nomFichier="top10_9.txt";
	else nomFichier="top10_16.txt";

	/*On ouvre le fichier en lecture*/
	FILE* fichierLecture=NULL;
	fichierLecture=fopen(nomFichier, "r");

	/*S'il n'est pas ouvert alors on affiche une erreur et on quitte*/
	if(!fichierLecture){
		fprintf(stderr, "Impossible d'ouvrire le fichier en lecture\n");
		exit(1);
	}

	char ligne[100];
	int score_t[10] = {0};
	char score_n[10][30];
	char s_valeur[100]="\0";
	char v[2]={'0', '\0'};
	size_t k=0;

	//On initialise le tableau des noms de score
	for(size_t i=0; i<10; i++)
		for(size_t j=0; j<30; j++)
			score_n[i][j]='\0';

	for(size_t i=0; i<10; i++){
		fgets(ligne, sizeof(ligne), fichierLecture);

		for(k=0; k<strlen(ligne); k++){
			if(ligne[k] == ' ')
				break;
			else {
				v[0]= ligne[k];
				strcat(s_valeur, v);
			}
		}
		// on copie le score recupere a la ligne i pour le mettre dans la structure de scores
		score_t[i]=atoi(s_valeur);
		// on vide la chaine de caracteres qui contient le score

		for(size_t j=0; j<100; j++)
			s_valeur[j]='\0';

		for(k+=1; k<strlen(ligne); k++){
			if(ligne[k] == '\n')
				break;
			v[0]=ligne[k];
			strcat(s_valeur, v);
		}
		// on copie le pseudo du score en question recupere a la ligne i pour le mettre dans la structure de scores
		strcat(score_n[i], s_valeur);
		// on vide la chaine de caracteres qui contient le pseudo
		for(size_t j=0; j<100; j++)
			s_valeur[j]='\0';
		//s_valeur="\0";/**/
	}

	fclose(fichierLecture);

	char nom[30]={""};

	int positionNouveauNom=insererPetiteValeur(score_t, score_n, temps, nom);

	//On met le nom a tel position;
	if(positionNouveauNom>-1){
		demanderNom(nom);
		for(size_t i=0; i<10; i++)
			score_n[positionNouveauNom][i]= '\0';
		strcat(score_n[positionNouveauNom], nom);
	}

		/*=========Maintenant on ecrit dans le fichier==========*/


	/*On ouvre le fichier en ecriture*/
	FILE* fichierEcriture=NULL;
	fichierEcriture=fopen(nomFichier, "w");

	/*S'il n'est pas ouvert alors on affiche une erreur et on quitte*/
	if(!fichierEcriture){
		fprintf(stderr, "Impossible d'ouvrire le fichier en ecriture\n");
		exit(1);
	}

	for(size_t i=0; i<10; i++){
        fprintf(fichierEcriture, "%d %s\n", score_t[i], score_n[i]);
	}
	fclose(fichierEcriture);
}


void reinitialiserTop10(size_t taille){

	char* nomFichier="";
	if(taille==4)
		nomFichier="top10_4.txt";
	else if(taille==9)
		nomFichier="top10_9.txt";
	else nomFichier="top10_16.txt";

	/*On ouvre le fichier en ecriture*/
	FILE* fichierEcriture=NULL;
	fichierEcriture=fopen(nomFichier, "w");

	/*S'il n'est pas ouvert alors on affiche une erreur et on quitte*/
	if(!fichierEcriture){
		fprintf(stderr, "Impossible d'ouvrire le fichier en ecriture\n");
		exit(1);
	}

	for(size_t i=0; i<10; i++){
        fprintf(fichierEcriture, "0 \n");
	}

	fclose(fichierEcriture);

}


void afficherTop10(size_t taille){
	/*On recupere le nom du fichier*/
	char* nomFichier="";
	if(taille==4)
		nomFichier="top10_4.txt";
	else if(taille==9)
		nomFichier="top10_9.txt";
	else nomFichier="top10_16.txt";

	/*On ouvre le fichier en lecture*/
	FILE* fichierLecture=NULL;
	fichierLecture=fopen(nomFichier, "r");

	/*S'il n'est pas ouvert alors on affiche une erreur et on quitte*/
	if(!fichierLecture){
		fprintf(stderr, "Impossible d'ouvrire le fichier en lecture\n");
		exit(1);
	}

	char ligne[100];
	int score_t[10] = {0};
	char score_n[10][30];
	char s_valeur[100]="\0";
	char v[2]={'0', '\0'};
	size_t k=0;

	//On initialise le tableau des noms de score
	for(size_t i=0; i<10; i++)
		for(size_t j=0; j<30; j++)
			score_n[i][j]='\0';

	for(size_t i=0; i<10; i++){
		fgets(ligne, sizeof(ligne), fichierLecture);

		for(k=0; k<strlen(ligne); k++){
			if(ligne[k] == ' ')
				break;
			else {
				v[0]= ligne[k];
				strcat(s_valeur, v);
			}
		}
		// on copie le score recupere a la ligne i pour le mettre dans la structure de scores
		score_t[i]=atoi(s_valeur);
		// on vide la chaine de caracteres qui contient le score

		for(size_t j=0; j<100; j++)
			s_valeur[j]='\0';

		for(k+=1; k<strlen(ligne); k++){
			if(ligne[k] == '\n')
				break;
			v[0]=ligne[k];
			strcat(s_valeur, v);
		}
		// on copie le pseudo du score en question recupere a la ligne i pour le mettre dans la structure de scores
		strcat(score_n[i], s_valeur);
		// on vide la chaine de caracteres qui contient le pseudo
		for(size_t j=0; j<100; j++)
			s_valeur[j]='\0';
	}

	fclose(fichierLecture);


	printf("__ Affichage du Top10 __\n");

	printf(" Temps\t\t Nom\n");

	for(size_t i=0;i<10; i++)
		if(score_t[i]!=0){
			size_t heu=score_t[i]/3600;
			size_t min=(score_t[i]/60)%60;
			size_t sec=score_t[i]%60;

			if(heu<10)
				printf("0");
			printf("%zu:", heu);
			if(min<10)
				printf("0");
			printf("%zu:", min);
			if(sec<10)
				printf("0");
			printf("%zu\t", sec);

			printf("%s\n", score_n[i]);
		}
}


/*Fonction qui resoud un sudoku entre par l'utilisateur*/
void recupeGrille(caseGrille**grille, size_t taille){
	//size_t taille; /*sera mis en parametre (avec pointeur)*/

	char nomFichier[30];
	fprintf(stdout, "Entez le nom/lien du fichier que vous voulez sauvegarder.");
	printf("  >> ");

	COULEUR_BLEU
	scanf("%s", nomFichier);
	COULEUR_ORIGINE

	/*On ouvre le fichier en lecture*/
	FILE* fichierLecture=NULL;
	fichierLecture=fopen(nomFichier, "r");

	/*S'il n'est pas ouvert alors on affiche une erreur et on quitte*/
	if(!fichierLecture){
		fprintf(stderr, "Impossible d'ouvrire le fichier en lecture\n");
		exit(1);
	}

	char ligne[50];
	char v[2]={"\0"};
	size_t k=0, l=0;

	for(size_t i=0; i<taille; i++){
		l=0;
		fgets(ligne, sizeof(ligne), fichierLecture);
		for(size_t j=0; j<strlen(ligne); j++){
			if(ligne[j]==' ' || ligne[j]=='\n'){
				grille[i][l].valeur=atoi(v);l++;
				v[0]='\0';
				v[1]='\0';
				k=0;
			}else{
				v[k++]=ligne[j];
			}
		}
	}

	fclose(fichierLecture);
}


/* ============ LIBERATION DE GRILLE ============ */

void libereGrille(caseGrille** grille, size_t taille){
	size_t iterateur;
	for(iterateur=0; iterateur<taille; iterateur++){
		free(grille[iterateur]); /* liberation de la deuxieme dimension de la grille */
	}
	free(grille); /* liberation de la premiere dimension de la grille */
}


