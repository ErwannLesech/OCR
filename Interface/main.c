#include <gtk/gtk.h>

void interface (GtkApplication *app)
{
	GtkWidget *window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 500);
	GtkWidget *button = gtk_button_new_with_label ("Test");
	gtk_widget_show (window);
}

int main (int argc, char **argv)
{
	GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "interface", G_CALLBACK (interface), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
