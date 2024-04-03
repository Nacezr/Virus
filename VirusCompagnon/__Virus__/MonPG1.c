#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *taille_entry, *poids_entry, *imc_label, *imc_label2;
float taille, poids;

// fonction qui permet de calculer l'IMC
void calcul_imc(GtkButton *button, gpointer user_data)
{
    // récupérer les valeurs entrées par l'utilisateur
    const gchar *taille_text = gtk_entry_get_text(GTK_ENTRY(taille_entry));
    const gchar *poids_text = gtk_entry_get_text(GTK_ENTRY(poids_entry));

    // calculer l'IMC
    taille = atof(taille_text);
    poids = atof(poids_text);
    float imc = poids / (taille / 100 * taille / 100);
    char imc_str[50];
    snprintf(imc_str, sizeof(imc_str), "Votre IMC est de %.2f", imc);
    gtk_label_set_text(GTK_LABEL(imc_label), imc_str);
    // afficher le résultat
    if (imc < 18)
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Insuffisance pondérale (maigreur)");
    }
    else if (18 > imc && imc < 25)
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Corpulence normale");
    }
    else if (25 > imc && imc < 30)
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Surpoids");
    }
    else if (30 > imc && imc < 35)
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Obésité modérée");
    }

    else if (35 > imc && imc < 40)
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Obésité sévère");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(imc_label2), "Obésité morbide");
    }
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkBuilder *builder;
    // Initialisation de GTK+
    gtk_init(&argc, &argv);
    // Chargement du fichier XML
    builder = gtk_builder_new_from_file("./glade/imc.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "IMC");
    // Récupération des widgets
    taille_entry = GTK_WIDGET(gtk_builder_get_object(builder, "taille_entry"));
    poids_entry = GTK_WIDGET(gtk_builder_get_object(builder, "poids_entry"));
    imc_label = GTK_WIDGET(gtk_builder_get_object(builder, "resultat"));
    imc_label2 = GTK_WIDGET(gtk_builder_get_object(builder, "resultat2"));
    // Connexion des signaux
    GtkWidget *calcul_button;
    calcul_button = GTK_WIDGET(gtk_builder_get_object(builder, "calcul_button"));
    g_signal_connect(calcul_button, "clicked", G_CALLBACK(calcul_imc), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage de la fenêtre
    gtk_widget_show_all(window);
    gtk_main();

    return EXIT_SUCCESS;
}