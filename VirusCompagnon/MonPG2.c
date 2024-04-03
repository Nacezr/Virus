#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

// Fonction de callback pour les boutons numériques et décimale
void on_button_clicked(GtkWidget *button, gpointer data) {
    const gchar *label = gtk_button_get_label(GTK_BUTTON(button));
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);
    gchar *new_text = g_strdup_printf("%s%s", text, label);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

// Fonction de callback pour les boutons opérateurs (+, -, *, /)
void on_operator_clicked(GtkWidget *button, gpointer data) {
    const gchar *operator = gtk_button_get_label(GTK_BUTTON(button));
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);
    gchar *new_text = g_strdup_printf("%s %s ", text, operator);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

// Fonction de callback pour le bouton racine carrée
void on_sqrt_clicked(GtkWidget *button, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);
    double operand = atof(text);
    double result = sqrt(operand);
    gchar *result_str = g_strdup_printf("%g", result);
    gtk_entry_set_text(entry, result_str);
    g_free(result_str);
}

// Fonction de callback pour le bouton égal
void on_equal_clicked(GtkWidget *button, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);
    gdouble result = 0;
    if (text[0] != '\0') {
        if (g_strrstr(text, " ")) {
            gchar **tokens = g_strsplit(text, " ", -1);
            if (g_strcmp0(tokens[0], "") != 0 && g_strcmp0(tokens[1], "") != 0 && g_strcmp0(tokens[2], "") != 0) {
                gdouble operand1 = atof(tokens[0]);
                gchar *operator = tokens[1];
                gdouble operand2 = atof(tokens[2]);
                if (g_strcmp0(operator, "+") == 0)
                    result = operand1 + operand2;
                else if (g_strcmp0(operator, "-") == 0)
                    result = operand1 - operand2;
                else if (g_strcmp0(operator, "*") == 0)
                    result = operand1 * operand2;
                else if (g_strcmp0(operator, "/") == 0) {
                    if (operand2 != 0)
                        result = operand1 / operand2;
                    else
                        gtk_entry_set_text(entry, "Erreur: Division par zéro");
                }
            }
            g_strfreev(tokens);
        } else {
            result = atof(text);
        }
    }
    gchar *result_str = g_strdup_printf("%g", result);
    gtk_entry_set_text(entry, result_str);
    g_free(result_str);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculatrice");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 20);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    
    gchar *num_labels[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0", "."};
    for (int i = 0; i < 11; i++) {
        GtkWidget *button = gtk_button_new_with_label(num_labels[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, i / 4 + 1, 1, 1);
    }
    
    gchar *operator_labels[] = {"+", "-", "*", "/", "sqrt", "=","+", "-"};
    for (int i = 0; i < 8; i++) {
        GtkWidget *button = gtk_button_new_with_label(operator_labels[i]);
        if (i == 4)
            g_signal_connect(button, "clicked", G_CALLBACK(on_sqrt_clicked), entry);
        else if (i == 5)
            g_signal_connect(button, "clicked", G_CALLBACK(on_equal_clicked), entry);
        else
            g_signal_connect(button, "clicked", G_CALLBACK(on_operator_clicked), entry);
        gtk_grid_attach(GTK_GRID(grid), button, 3, i + 1, 1, 1);
    }
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}
