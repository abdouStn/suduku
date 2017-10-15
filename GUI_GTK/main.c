//#include <config.h>
//#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include<gdk-pixbuf/gdk-pixbuf.h>
#include "fonctions.h"
#include "gtk-sudoku.h"
#include <string.h>
#include<time.h>


//#include <glib/gi18n.h>

// gcc main.c $(pkg-config --libs --cflags gtk+-2.0) -o main

#define UTF8(string) g_locale_to_utf8(string, -1, NULL, NULL, NULL)

/*static */GtkWidget *MainWindow=NULL;
/*static */
GtkWidget *MenuWidget=NULL;
/*static */
GtkWidget *ChoixTaille=NULL;
/*static */
GtkWidget *taille=NULL;
/*static */
GtkWidget *BoutonTaille[3];
/*static */
GtkWidget *TopWidget=NULL;
/*static */
GtkWidget *BoutonMenu[4];
/*static */
GtkWidget *image=NULL;
/*static */
GtkWidget **tableGenerale=NULL;
/*static */
GtkWidget *tableGrille=NULL;

int tailleDeGrille=0;



void AfficheChoixTaille()
{
    gtk_widget_destroy(MainWindow);
    Taille();
}
void AfficheJeu4()
{
    gtk_widget_destroy(MainWindow);
    New4();
}
void AfficheJeu9()
{
    gtk_widget_destroy(MainWindow);
    New9();
}
void AfficheJeu16()
{
    gtk_widget_destroy(MainWindow);
    New16();
}
void FenetrePrincipale()
{


    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);


    //BEGIN PARAM FENETRE
    MainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 320, 200);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Menu");

    //END PARAM FENETRE
    image = gtk_image_new_from_file ("titre.png");

    BoutonMenu[0] = gtk_button_new_with_label ("Nouvelle Partie");
    BoutonMenu[1] = gtk_button_new_with_label ("Charger Partie");
    BoutonMenu[2] = gtk_button_new_with_label ("Top 10");
    BoutonMenu[3] = gtk_button_new_with_label ("Quitter");

    // Une table sert a stocker les widgets de maniere ordonnee.
    MenuWidget = gtk_table_new (0, 0, 0);

    // On ajoute la table au widget fenetre.
    gtk_container_add(GTK_CONTAINER(MainWindow), MenuWidget);

    // On positionne l'image et les boutons dans la table.
    gtk_table_attach(GTK_TABLE(MenuWidget), image,
                     1, 2, 1, 2, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(MenuWidget), BoutonMenu[0],
                     1, 2, 2, 3, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(MenuWidget), BoutonMenu[1],
                     1, 2, 3, 4, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(MenuWidget), BoutonMenu[2],
                     1, 2, 4, 5, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(MenuWidget), BoutonMenu[3],
                     1, 2, 5, 6, GTK_FILL, GTK_FILL, 20,5);

    g_signal_connect(G_OBJECT(BoutonMenu[0]),"clicked", G_CALLBACK(AfficheChoixTaille),NULL);
    g_signal_connect(G_OBJECT(BoutonMenu[2]),"clicked", G_CALLBACK(AfficheChoixTaille),NULL);
    g_signal_connect(G_OBJECT(BoutonMenu[3]),"clicked", G_CALLBACK(gtk_main_quit),NULL);



    // encodage
    //gchar *chaine = UTF8("Un texte accentué, avec des caractères bizarres... $23, 32?, £18...");
    //g_free(chaine);
}


// Fonction pour crÃ©er un GtkImage* en fonction du chiffre Ã  afficher

GtkWidget *creeNouvelleImage(int valeur)
{
    if(valeur==0)
    {
        return gtk_image_new_from_file("Police/CaseVide.jpg");
    }
    if(valeur==1)
    {
        return gtk_image_new_from_file("Police/CaseValide/1.jpg");
    }
    if(valeur==2)
    {
        return gtk_image_new_from_file("Police/CaseValide/2.jpg");
    }
    if(valeur==3)
    {
        return gtk_image_new_from_file("Police/CaseValide/3.jpg");
    }
    if(valeur==4)
    {
        return gtk_image_new_from_file("Police/CaseValide/4.jpg");
    }
    if(valeur==5)
    {
        return gtk_image_new_from_file("Police/CaseValide/5.jpg");
    }
    if(valeur==6)
    {
        return gtk_image_new_from_file("Police/CaseValide/6.jpg");
    }
    if(valeur==7)
    {
        return gtk_image_new_from_file("Police/CaseValide/7.jpg");
    }
    if(valeur==8)
    {
        return gtk_image_new_from_file("Police/CaseValide/8.jpg");
    }
    if(valeur==9)
    {
        return gtk_image_new_from_file("Police/CaseValide/9.jpg");
    }
    if(valeur==10)
    {
        return gtk_image_new_from_file("Police/CaseValide/10.jpg");
    }
    if(valeur==11)
    {
        return gtk_image_new_from_file("Police/CaseValide/11.jpg");
    }
    if(valeur==12)
    {
        return gtk_image_new_from_file("Police/CaseValide/12.jpg");
    }
    if(valeur==13)
    {
        return gtk_image_new_from_file("Police/CaseValide/13.jpg");
    }
    if(valeur==14)
    {
        return gtk_image_new_from_file("Police/CaseValide/14.jpg");
    }
    if(valeur==15)
    {
        return gtk_image_new_from_file("Police/CaseValide/15.jpg");
    }
    if(valeur==16)
    {
        return gtk_image_new_from_file("Police/CaseValide/16.jpg");
    }
    return NULL;
}


void placerNouvelleImage(GtkWidget*image, int valeur)
{
    if(valeur==0)
    {
        return gtk_image_set_from_file(image, "Police/CaseVide.jpg");
    }
    if(valeur==1)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/1.jpg");
    }
    if(valeur==2)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/2.jpg");
    }
    if(valeur==3)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/3.jpg");
    }
    if(valeur==4)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/4.jpg");
    }
    if(valeur==5)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/5.jpg");
    }
    if(valeur==6)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/6.jpg");
    }
    if(valeur==7)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/7.jpg");
    }
    if(valeur==8)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/8.jpg");
    }
    if(valeur==9)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/9.jpg");
    }
    if(valeur==10)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/10.jpg");
    }
    if(valeur==11)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/11.jpg");
    }
    if(valeur==12)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/12.jpg");
    }
    if(valeur==13)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/13.jpg");
    }
    if(valeur==14)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/14.jpg");
    }
    if(valeur==15)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/15.jpg");
    }
    if(valeur==16)
    {
        return gtk_image_set_from_file(image, "Police/CaseEntree/16.jpg");
    }
    return NULL;
}

void placerNouvelleImageErreur(GtkWidget*image, int valeur)
{
    if(valeur==0)
    {
        return gtk_image_set_from_file(image, "Police/CaseVide.jpg");
    }
    if(valeur==1)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/1.jpg");
    }
    if(valeur==2)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/2.jpg");
    }
    if(valeur==3)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/3.jpg");
    }
    if(valeur==4)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/4.jpg");
    }
    if(valeur==5)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/5.jpg");
    }
    if(valeur==6)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/6.jpg");
    }
    if(valeur==7)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/7.jpg");
    }
    if(valeur==8)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/8.jpg");
    }
    if(valeur==9)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/9.jpg");
    }
    if(valeur==10)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/10.jpg");
    }
    if(valeur==11)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/11.jpg");
    }
    if(valeur==12)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/12.jpg");
    }
    if(valeur==13)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/13.jpg");
    }
    if(valeur==14)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/14.jpg");
    }
    if(valeur==15)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/15.jpg");
    }
    if(valeur==16)
    {
        return gtk_image_set_from_file(image, "Police/CaseInvalide/16.jpg");
    }
    return NULL;
}


GtkWidget *creerEventBox()
{
    return gtk_event_box_new();
}

GtkWidget* exWindow;
int indice;

void on_activate_entry(GtkWidget* bEntry, gpointer data)
{
    const char *sText;
    sText=(char*)gtk_entry_get_text(GTK_ENTRY(bEntry));
    gtk_label_set(GTK_LABEL((GtkWidget*)data), sText);
    int i=atoi(sText);
    if(i>0&&i<tailleDeGrille)
    {
        indice=i;
        printf(sText);
        gtk_widget_destroy(exWindow);
        creerEntryBox();
    }
    else
    {
        gtk_widget_destroy(exWindow);
        creerEntryBox();
        indice=0;
    }
}
void creerEntryBox()
{
    GtkWidget* bEntry=NULL;
    bEntry=gtk_entry_new_with_max_length(2);
    GtkWidget* valeur;
    GtkWidget* box;
    exWindow=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(exWindow), 90, 60);
    gtk_window_set_title(GTK_WINDOW(exWindow), "Valeur");
    valeur=gtk_label_new(NULL);
    box=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(exWindow), box);
    gtk_box_pack_start(GTK_BOX(box), bEntry, FALSE, FALSE, 0);
    g_signal_connect(G_OBJECT(bEntry), "activate", G_CALLBACK(on_activate_entry), (GtkWidget*) valeur);

}

gboolean fct_cb (GtkWidget * event_box, GdkEventButton * event, gpointer data)
{
    GtkWidget *image=data;
    creerEntryBox();
    placerNouvelleImage(data, indice);
    printf("Clic à la position (%f,%f).\n",event->x,event->y);
    printf("%d",indice);
    gtk_widget_show_all(exWindow);
    return TRUE;
}

void New4()
{
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 300);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Sudoku");

    tailleDeGrille=4;
    caseGrille **Grille4=NULL;
    Grille4=initGrille(4);
    uint8_t *tabVal=malloc(4*sizeof(uint8_t));
    melangerTableauValeurs(tabVal,4);
    genererGrilleComplete(Grille4,0,4,tabVal);
    genererGrilleJeu(Grille4,4,tabVal);

    GtkWidget *SuperBox=NULL;
    GtkWidget *SousFenetre1=NULL;
    GtkWidget *SousFenetre2=NULL;
    GtkWidget *SousFenetre1_1=NULL;
    GtkWidget *ImageSudoku=NULL;
    GtkWidget *BoutonValidation;


    ImageSudoku=gtk_image_new_from_file("titre.png");
    BoutonValidation = gtk_button_new_with_label ("Vérifier");


    SuperBox=gtk_vbox_new(FALSE,0);
    SousFenetre1=gtk_hbox_new(TRUE,0);
    SousFenetre2=gtk_hbox_new(TRUE,0);
    SousFenetre1_1=gtk_hbox_new(FALSE,0);

    gtk_container_add(GTK_CONTAINER(MainWindow),SuperBox);

    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre2,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre1),SousFenetre1_1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),ImageSudoku,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),BoutonValidation,FALSE,FALSE,0);



    // On aura besoin de 4 GtkBox (1 par ligne)
    // elles seront stockÃ©es dans ce tableau

    GtkWidget **lignes=NULL;
    lignes = (GtkWidget **) g_malloc(4*sizeof(GtkWidget *));

    // On aura besoin de 4*4 GtkImage
    // idem, on alloue un tableau de tableau de GtkWidget*

    GtkWidget ***images=NULL;
    images = (GtkWidget ***) g_malloc(4*sizeof(GtkWidget **));

    GtkWidget ***eventB=NULL;
    eventB = (GtkWidget ***) g_malloc(4*sizeof(GtkWidget **));

    for(int n=0; n<4; n++)
    {
        images[n] = (GtkWidget **) g_malloc(4*sizeof(GtkWidget *));
        eventB[n] = (GtkWidget **) g_malloc(4*sizeof(GtkWidget *));

    }

    // Boucle pour crÃ©er les images

    for(int j=0; j<4; j++)
    {
        // Au dÃ©part de chaque ligne on crÃ©e un GtkBox
        // et on l'ajoute Ã  la fenetre

        lignes[j] = gtk_vbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(SousFenetre1_1),lignes[j],FALSE,FALSE,0);

        // Ensuite on emplit les 4 cases de la ligne
        // qu'on vient de crÃ©er

        for(int i=0; i<4; i++)
        {
            images[j][i] = creeNouvelleImage(Grille4[j][i].valeur);
            if (Grille4[j][i].valeur==0)
            {
                eventB[j][i] = creerEventBox();
                gtk_container_add(GTK_CONTAINER(eventB[j][i]),images[j][i]);
                gtk_box_pack_start(GTK_BOX(lignes[j]),eventB[j][i],FALSE,FALSE,0);
                g_signal_connect(G_OBJECT(eventB[j][i]),"button_press_event",G_CALLBACK(fct_cb),images[j][i]);
            }
            else
            {
                gtk_box_pack_start(GTK_BOX(lignes[j]),images[j][i],FALSE,FALSE,0);
            }
        }
        gtk_widget_show_all(MainWindow);
    }
}

void New9()
{
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 300);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Sudoku");
    tailleDeGrille=9;
    caseGrille **Grille9=NULL;
    Grille9=initGrille(9);
    uint8_t *tabVal=malloc(9*sizeof(uint8_t));
    melangerTableauValeurs(tabVal,9);
    genererGrilleComplete(Grille9,0,9,tabVal);
    genererGrilleJeu(Grille9,9,tabVal);

    GtkWidget *SuperBox=NULL;
    GtkWidget *SousFenetre1=NULL;
    GtkWidget *SousFenetre2=NULL;
    GtkWidget *SousFenetre1_1=NULL;
    GtkWidget *ImageSudoku=NULL;
    GtkWidget *BoutonValidation;


    ImageSudoku=gtk_image_new_from_file("titre.png");
    BoutonValidation = gtk_button_new_with_label ("Vérifier");


    SuperBox=gtk_vbox_new(FALSE,0);
    SousFenetre1=gtk_hbox_new(TRUE,0);
    SousFenetre2=gtk_hbox_new(TRUE,0);
    SousFenetre1_1=gtk_hbox_new(FALSE,0);

    gtk_container_add(GTK_CONTAINER(MainWindow),SuperBox);

    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre2,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre1),SousFenetre1_1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),ImageSudoku,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),BoutonValidation,FALSE,FALSE,0);



    // On aura besoin de 4 GtkBox (1 par ligne)
    // elles seront stockÃ©es dans ce tableau

    GtkWidget **lignes=NULL;
    lignes = (GtkWidget **) g_malloc(9*sizeof(GtkWidget *));

    // On aura besoin de 4*4 GtkImage
    // idem, on alloue un tableau de tableau de GtkWidget*

    GtkWidget ***images=NULL;
    images = (GtkWidget ***) g_malloc(9*sizeof(GtkWidget **));

    GtkWidget ***eventB=NULL;
    eventB = (GtkWidget ***) g_malloc(9*sizeof(GtkWidget **));

    for(int n=0; n<9; n++)
    {
        images[n] = (GtkWidget **) g_malloc(9*sizeof(GtkWidget *));
        eventB[n] = (GtkWidget **) g_malloc(9*sizeof(GtkWidget *));

    }

    // Boucle pour crÃ©er les images

    for(int j=0; j<9; j++)
    {
        // Au dÃ©part de chaque ligne on crÃ©e un GtkBox
        // et on l'ajoute Ã  la fenetre

        lignes[j] = gtk_vbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(SousFenetre1_1),lignes[j],FALSE,FALSE,0);

        // Ensuite on emplit les 4 cases de la ligne
        // qu'on vient de crÃ©er

        for(int i=0; i<9; i++)
        {
            images[j][i] = creeNouvelleImage(Grille9[j][i].valeur);
            if (Grille9[j][i].valeur==0)
            {
                eventB[j][i] = creerEventBox();
                gtk_container_add(GTK_CONTAINER(eventB[j][i]),images[j][i]);
                gtk_box_pack_start(GTK_BOX(lignes[j]),eventB[j][i],FALSE,FALSE,0);
                g_signal_connect(G_OBJECT(eventB[j][i]),"button_press_event",G_CALLBACK(fct_cb),images[j][i]);
            }
            else
            {
                gtk_box_pack_start(GTK_BOX(lignes[j]),images[j][i],FALSE,FALSE,0);
            }

        }
        gtk_widget_show_all(MainWindow);
    }
}


void New16()
{
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 300);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Sudoku");
    tailleDeGrille=16;
    caseGrille **Grille16=NULL;
    Grille16=initGrille(16);
    uint8_t *tabVal=malloc(16*sizeof(uint8_t));
    melangerTableauValeurs(tabVal,16);
    genererGrilleComplete(Grille16,0,16,tabVal);
    genererGrilleJeu(Grille16,16,tabVal);

    GtkWidget *SuperBox=NULL;
    GtkWidget *SousFenetre1=NULL;
    GtkWidget *SousFenetre2=NULL;
    GtkWidget *SousFenetre1_1=NULL;
    GtkWidget *ImageSudoku=NULL;
    GtkWidget *BoutonValidation;


    ImageSudoku=gtk_image_new_from_file("titre.png");
    BoutonValidation = gtk_button_new_with_label ("Vérifier");


    SuperBox=gtk_vbox_new(FALSE,0);
    SousFenetre1=gtk_hbox_new(TRUE,0);
    SousFenetre2=gtk_hbox_new(TRUE,0);
    SousFenetre1_1=gtk_hbox_new(FALSE,0);

    gtk_container_add(GTK_CONTAINER(MainWindow),SuperBox);

    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SuperBox),SousFenetre2,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre1),SousFenetre1_1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),ImageSudoku,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(SousFenetre2),BoutonValidation,FALSE,FALSE,0);



    // On aura besoin de 4 GtkBox (1 par ligne)
    // elles seront stockÃ©es dans ce tableau

    GtkWidget **lignes=NULL;
    lignes = (GtkWidget **) g_malloc(16*sizeof(GtkWidget *));

    // On aura besoin de 4*4 GtkImage
    // idem, on alloue un tableau de tableau de GtkWidget*

    GtkWidget ***images=NULL;
    images = (GtkWidget ***) g_malloc(16*sizeof(GtkWidget **));

    GtkWidget ***eventB=NULL;
    eventB = (GtkWidget ***) g_malloc(16*sizeof(GtkWidget **));

    for(int n=0; n<16; n++)
    {
        images[n] = (GtkWidget **) g_malloc(16*sizeof(GtkWidget *));
        eventB[n] = (GtkWidget **) g_malloc(16*sizeof(GtkWidget *));

    }

    // Boucle pour crÃ©er les images

    for(int j=0; j<16; j++)
    {
        // Au dÃ©part de chaque ligne on crÃ©e un GtkBox
        // et on l'ajoute Ã  la fenetre

        lignes[j] = gtk_vbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(SousFenetre1_1),lignes[j],FALSE,FALSE,0);

        // Ensuite on emplit les 4 cases de la ligne
        // qu'on vient de crÃ©er

        for(int i=0; i<16; i++)
        {
            images[j][i] = creeNouvelleImage(Grille16[j][i].valeur);
            if (Grille16[j][i].valeur==0)
            {
                eventB[j][i] = creerEventBox();
                gtk_container_add(GTK_CONTAINER(eventB[j][i]),images[j][i]);
                gtk_box_pack_start(GTK_BOX(lignes[j]),eventB[j][i],FALSE,FALSE,0);
                g_signal_connect(G_OBJECT(eventB[j][i]),"button_press_event",G_CALLBACK(fct_cb),images[j][i]);
            }
            else
            {
                gtk_box_pack_start(GTK_BOX(lignes[j]),images[j][i],FALSE,FALSE,0);
            }

        }
        gtk_widget_show_all(MainWindow);
    }
}

void Taille()
{

    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 320, 200);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Choix de la taille");
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);


    BoutonTaille[0] = gtk_button_new_with_label ("4x4");
    BoutonTaille[1] = gtk_button_new_with_label ("9x9");
    BoutonTaille[2] = gtk_button_new_with_label ("16x16");


    // Une table sert a stocker les widgets de maniere ordonnee.
    taille = gtk_table_new (0, 0, 0);

    // On ajoute la table au widget fenetre.
    gtk_container_add(GTK_CONTAINER(MainWindow), taille);

    // On positionne l'image et les boutons dans la table.

    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[0],
                     1, 2, 2, 3, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[1],
                     1, 2, 3, 4, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[2],
                     1, 2, 4, 5, GTK_FILL, GTK_FILL, 20, 5);
    gtk_widget_show_all(MainWindow);

    g_signal_connect(G_OBJECT(BoutonTaille[0]),"clicked", G_CALLBACK(AfficheJeu4),NULL);
    g_signal_connect(G_OBJECT(BoutonTaille[1]),"clicked", G_CALLBACK(AfficheJeu9),NULL);
    g_signal_connect(G_OBJECT(BoutonTaille[2]),"clicked", G_CALLBACK(AfficheJeu16),NULL);


}

void Top()
{

    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 320, 200);
    gtk_window_set_title (GTK_WINDOW (MainWindow), "Top 10");

    BoutonTaille[0] = gtk_button_new_with_label ("4x4");
    BoutonTaille[1] = gtk_button_new_with_label ("9x9");
    BoutonTaille[2] = gtk_button_new_with_label ("16x16");

    // Une table sert a stocker les widgets de maniere ordonnee.
    taille = gtk_table_new (0, 0, 0);

    // On ajoute la table au widget fenetre.
    gtk_container_add(GTK_CONTAINER(MainWindow), taille);

    // On positionne l'image et les boutons dans la table.

    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[0],
                     1, 2, 2, 3, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[1],
                     1, 2, 3, 4, GTK_FILL, GTK_FILL, 20, 5);
    gtk_table_attach(GTK_TABLE(taille), BoutonTaille[2],
                     1, 2, 4, 5, GTK_FILL, GTK_FILL, 20, 5);
    gtk_widget_show_all(MainWindow);

}
int main (int argc, char *argv[])
{
#ifdef ENABLE_NLS
    bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
#endif

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);
    srand(time(NULL));

    // On cree la fenetre principale
    FenetrePrincipale();
    /* Affichage et boucle évènementielle */
    gtk_widget_show_all(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}

