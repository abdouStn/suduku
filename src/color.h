#ifndef BG_LIGHT

/**********************************************
 *			LES COULEUS DU TERMINAL			  *
 *--------------------------------------------*
 *   auteur: Stella Zevio			  *
 *   date: 15 mars 2012						  *
 **********************************************/



// texte
#define BLACK    "\033[1;30m"
#define RED      "\033[1;31m"
#define GREEN    "\033[1;32m"
#define YELLOW   "\033[1;33m"
#define BLUE     "\033[1;34m"
#define PURPLE   "\033[1;35m"
#define CYAN     "\033[1;36m"
#define GREY     "\033[1;37m"

// background
#define BG_BLACK   "\033[1;40m"
#define BG_RED    	"\033[1;41m"
#define BG_GREEN    "\033[1;42m"
#define BG_YELLOW  	"\033[1;43m"
#define BG_BLUE    	"\033[1;44m"
#define BG_PURPLE   "\033[1;45m"
#define BG_CYAN     "\033[1;46m"
#define BG_GREY     "\033[1;47m"

#define BBARRER    	"\033[1;9m"
#define REINIT	 "\033[1;0m"
#define GRAS     "\033[1;1m"
#define SOULIGNE "\033[1;4m"
#define INVERSER "\033[1;7m"  // inverse les couleurs texte et background 
#define clear    	"\033[H;033[2J" // remet le curseur en haut de la console.

#else // else BG_LIGHT
// texte
#define BLACK    "\033[0;30m"
#define RED      "\033[0;31m"
#define GREEN    "\033[0;32m"
#define YELLOW   "\033[0;33m"
#define BLUE     "\033[0;34m"
#define PURPLE   "\033[0;35m"
#define CYAN     "\033[0;36m"
#define GREY     "\033[0;37m"

// background
#define BG_BLACK   "\033[0;40m"
#define BG_RED    	"\033[0;41m"
#define BG_GREEN    "\033[0;42m"
#define BG_YELLOW  	"\033[0;43m"
#define BG_BLUE    	"\033[0;44m"
#define BG_PURPLE   "\033[0;45m"
#define BG_CYAN     "\033[0;46m"
#define BG_GREY     "\033[0;47m"


#define BBARRER		"\033[0;9m"
#define REINIT		"\033[0;0m"
#define GRAS		"\033[0;1m"
#define SOULIGNE	"\033[0;4m"
#define INVERSER	"\033[0;7m"  // inverse les couleurs texte et background 
#define clear		"\033[H;033[2J" // remet le curseur en haut de la console "fait un bug" .


#endif // endif BG_LIGHT

#define DEFAULT_COLOR "\033[0;m"

