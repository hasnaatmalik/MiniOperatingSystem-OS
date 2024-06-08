#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct ThreadData {
    int secretNumber;
    GtkWidget *label;
    GtkWidget *entry;
};

// Function to handle button click event
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    ThreadData *threadData = static_cast<ThreadData *>(data);
    int secretNumber = threadData->secretNumber;
    GtkWidget *label = threadData->label;
    GtkWidget *entry = threadData->entry;

    const gchar *input = gtk_entry_get_text(GTK_ENTRY(entry));
    int guess = atoi(input);

    if (guess < secretNumber) {
        gtk_label_set_text(GTK_LABEL(label), "Too low! Try again.");
    } else if (guess > secretNumber) {
        gtk_label_set_text(GTK_LABEL(label), "Too high! Try again.");
    } else {
        gtk_label_set_text(GTK_LABEL(label), "Congratulations! You guessed the number.");
    }
}

// Function to create GUI
void createGUI(ThreadData *threadData) {
    gtk_init(NULL, NULL);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Guessing Game");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label = gtk_label_new("Enter your guess:");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

    GtkWidget *button = gtk_button_new_with_label("Guess");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), threadData);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    GtkWidget *resultLabel = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), resultLabel, TRUE, TRUE, 0);

    // Set thread data
    threadData->label = resultLabel;
    threadData->entry = entry;

    gtk_widget_show_all(window);

    gtk_main();
}

int main(int argc, char *argv[]) {
    srand(time(0));

    ThreadData threadData;
    threadData.secretNumber = rand() % 100 + 1;

    createGUI(&threadData);

    return 0;
}
