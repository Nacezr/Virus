#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *celsius_entry, *fahrenheit_entry;

// Fonction de conversion de Celsius en Fahrenheit
double celsius_to_fahrenheit(double celsius) {
    return (celsius * 9 / 5) + 32;
}

// Fonction de conversion de Fahrenheit en Celsius
double fahrenheit_to_celsius(double fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

// Fonction appelée lors du clic sur le bouton de conversion Celsius vers Fahrenheit
void on_convert_to_fahrenheit(GtkButton *button, gpointer user_data) {
    const gchar *celsius_str = gtk_entry_get_text(GTK_ENTRY(celsius_entry));
    double celsius = atof(celsius_str);
    double fahrenheit = celsius_to_fahrenheit(celsius);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", fahrenheit);
    gtk_entry_set_text(GTK_ENTRY(fahrenheit_entry), buffer);
}

// Fonction appelée lors du clic sur le bouton de conversion Fahrenheit vers Celsius
void on_convert_to_celsius(GtkButton *button, gpointer user_data) {
    const gchar *fahrenheit_str = gtk_entry_get_text(GTK_ENTRY(fahrenheit_entry));
    double fahrenheit = atof(fahrenheit_str);
    double celsius = fahrenheit_to_celsius(fahrenheit);
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", celsius);
    gtk_entry_set_text(GTK_ENTRY(celsius_entry), buffer);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *label1, *label2, *button1, *button2;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Convertisseur d'unités");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    label1 = gtk_label_new("Celsius:");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);

    celsius_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), celsius_entry, 1, 0, 1, 1);

    button1 = gtk_button_new_with_label("Convertir");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_convert_to_fahrenheit), NULL);
    gtk_grid_attach(GTK_GRID(grid), button1, 2, 0, 1, 1);

    label2 = gtk_label_new("Fahrenheit:");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);

    fahrenheit_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), fahrenheit_entry, 1, 1, 1, 1);

    button2 = gtk_button_new_with_label("Convertir");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_convert_to_celsius), NULL);
    gtk_grid_attach(GTK_GRID(grid), button2, 2, 1, 1, 1);

    gtk_container_add(GTK_CONTAINER(window), grid);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
