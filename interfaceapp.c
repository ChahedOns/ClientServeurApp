#include <gtk/gtk.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/wait.h>
    GtkLabel *mylabel; // Label
    GtkWidget *app; // Window
	GtkBuilder *builder; // GTK Builder variable
    GtkTextView *viewC, *viewS, *viewSP, *viewCP;

    int x =3;
// Main function
int main(int argc, char *argv[])
{
    // Variables
  
	gtk_init(&argc, &argv); // Start GTK

	builder = gtk_builder_new(); // Create GTK UI Builder
	gtk_builder_add_from_file(builder, "interface.glade", NULL); // Load our UI file

	// Assign the Variables
	app = GTK_WIDGET(gtk_builder_get_object (builder,"Window1")); 
    if (NULL == app)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"Window1\" \n");
        /* Your error handling code goes here */
    }
	mylabel = GTK_LABEL(gtk_builder_get_object(builder, "MyLabel")); // Load our label named MyLabel
	// Essential for a GTK based program
	gtk_builder_connect_signals(builder, NULL); 
	g_object_unref(builder);
	
	gtk_widget_show_all(app); // Show our window
    
	gtk_main(); // Run our program

	return 0; // Necessary for a c main function
}
// Function to exit our app
void exit_app()
{
	printf("Exit app \n"); // Not neccesary
	gtk_main_quit(); // Command to quit a GTK program
}

// Function when our button is pressed
void clicked_np()
{
    gtk_widget_destroy(app);
    GtkWidget *window1;
    GtkBuilder *builder1; // GTK Builder variable
    GtkLabel *mylabel1;
    //system ("./serveur");
    builder1 = gtk_builder_new(); // Create GTK UI Builder
	gtk_builder_add_from_file(builder1, "interface.glade", NULL); // Load our UI file
	// Assign the Variables
	window1 = GTK_WIDGET(gtk_builder_get_object (builder1,"Window3")); 
    if (NULL == window1)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"Window3\" \n");
        /* Your error handling code goes here */
    }
	mylabel1 = GTK_LABEL(gtk_builder_get_object(builder1, "MyLabel3")); // Load our label named MyLabel
    gtk_builder_connect_signals(builder1, NULL); 
    gtk_widget_show_all(window1);
    gtk_main();
}
void serveur_btn_np(){
    int p1= fork();
    if (p1>0){
        system("./serveurNP");
        wait(&x);
    }
}
void client_btn_np()
{
    int p1= fork();
    if (p1>0){
        printf("*************************************************************** \n");
        system("./clientNP");
        wait(&x);
        }
}
void clicked_sk()
{
    gtk_widget_destroy(app);
    GtkWidget *window;
    GtkBuilder *builder2; // GTK Builder variable
    GtkLabel *mylabel2;
    //system ("./serveur");
    builder2 = gtk_builder_new(); // Create GTK UI Builder
	gtk_builder_add_from_file(builder2, "interface.glade", NULL); // Load our UI file
	// Assign the Variables
	window = GTK_WIDGET(gtk_builder_get_object (builder2,"Window2")); 
    if (NULL == window)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"Window2\" \n");
        /* Your error handling code goes here */
    }
	mylabel2 = GTK_LABEL(gtk_builder_get_object(builder2, "MyLabel2")); // Load our label named MyLabel
    gtk_builder_connect_signals(builder2, NULL); 
    gtk_widget_show_all(window);
    gtk_main();
}

void Serveur_btn_sk(){
    int p1= fork();
    if (p1>0){
        system("./serveurSK");
        wait(&x);
        }
}
void Client_btn_sk()
{
    int p1= fork();
    if (p1>0){
        printf("*************************************************************** \n");
        system("./clientSK");
        wait(&x);
        }
}
