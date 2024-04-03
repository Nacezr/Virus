#include <gtk/gtk.h>

GtkWidget *entry_exercice;
GtkWidget *entry_duree;
GtkWidget *label_resultat;

// Fonction pour calculer les calories brûlées en fonction du type d'exercice et de la durée
float calculer_calories_brulees(const char type_exercice[], float duree) {
    // Définir les calories brûlées par minute pour différents types d'exercice (hypothétique)
    float calories_par_minute = 0.0;
    if (strcmp(type_exercice, "marche") == 0) {
        calories_par_minute = 4.0;
    } else if (strcmp(type_exercice, "course") == 0) {
        calories_par_minute = 8.0;
    } else if (strcmp(type_exercice, "vélo") == 0) {
        calories_par_minute = 6.0;
    } else if (strcmp(type_exercice, "natation") == 0) {
        calories_par_minute = 7.0;
    } else {
        return -1.0; // Type d'exercice non reconnu
    }

    // Calculer les calories brûlées en fonction de la durée
    float calories_brulees = calories_par_minute * duree;
    return calories_brulees;
}

// Callback pour le bouton de calcul
void on_calculer_button_clicked(GtkWidget *widget, gpointer user_data) {
    const gchar *type_exercice = gtk_entry_get_text(GTK_ENTRY(entry_exercice));
    float duree = atof(gtk_entry_get_text(GTK_ENTRY(entry_duree)));

    // Calculer les calories brûlées
    float calories_brulees = calculer_calories_brulees(type_exercice, duree);

    // Afficher le résultat
    if (calories_brulees >= 0.0) {
        gchar *resultat_str = g_strdup_printf("Vous avez brûlé %.2f calories en faisant du %s pendant %.2f minutes.", calories_brulees, type_exercice, duree);
        gtk_label_set_text(GTK_LABEL(label_resultat), resultat_str);
        g_free(resultat_str);
    } else {
        gtk_label_set_text(GTK_LABEL(label_resultat), "Type d'exercice non reconnu");
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label_exercice;
    GtkWidget *label_duree;
    GtkWidget *button_calculer;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculateur de calories brûlées");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label_exercice = gtk_label_new("Type d'exercice:");
    gtk_grid_attach(GTK_GRID(grid), label_exercice, 0, 0, 1, 1);

    entry_exercice = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_exercice, 1, 0, 1, 1);

    label_duree = gtk_label_new("Durée (minutes):");
    gtk_grid_attach(GTK_GRID(grid), label_duree, 0, 1, 1, 1);

    entry_duree = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry_duree, 1, 1, 1, 1);

    button_calculer = gtk_button_new_with_label("Calculer");
    g_signal_connect(button_calculer, "clicked", G_CALLBACK(on_calculer_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_calculer, 0, 2, 2, 1);

    label_resultat = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), label_resultat, 0, 3, 2, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

