#include <gtk/gtk.h>
#include <string.h>;

GtkBuilder *builder;
GtkWidget *window = NULL;
gchar* file;
GtkStack *stack;
GtkStack *stack2;


int main_interface (int argc, char **argv)
{
	builder = NULL;
	GError *error = NULL;
    	gchar *filename = NULL;

	gtk_init(&argc,argv);

	builder = gtk_builder_new_from_file("interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	filename = g_build_filename("main.glade", NULL);

	if (!gtk_builder_add_from_file(builder, filename, &error)) // load file
    	{
        	g_warning("%s", error->message);
        	g_free(filename);
        	g_error_free(error);
        	return EXIT_FAILURE;
    	}
		
	gtk_widget_show_all(window);
	gtk_main;
	return EXIT_SUCCESS;
}
