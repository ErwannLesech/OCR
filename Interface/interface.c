#include <gtk/gtk.h>
#include <string.h>

static GtkBuilder* builder;
static GtkWidget* window;
static GtkWidget* fixed;
static GtkWidget* fileChooser;
static GtkWidget* button;
static GtkWidget* label;
static GtkWidget* preview;
static char* file;
static int cptEaster;

int valid_format(int len)
{
    	if (file[len-4] == '.' && file[len-3] == 'p'
            && ((file[len-2] == 'n' && file[len-1] == 'g')))
		return 1;

    	if (file[len-4] == '.' && file[len-3] == 'j'
	    && file[len-2] == 'p' && file[len-1] == 'g')
		return 1;
	return 0;
}

void updateImage(GtkFileChooser *fc){
    file = gtk_file_chooser_get_preview_filename(fc);
    if(file){
        if(valid_format(strlen(file))){
            gtk_label_set_text(GTK_LABEL(label), "The format is valid");
        } else {
            gtk_label_set_text(GTK_LABEL(label), "Please choose a .png or .jpg");
        }
        gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*) file);
    }
}

void callOCRProject(){
    if(file){
        size_t lenF = strlen(file);
        if(lenF == 0) 
	{
            switch(cptEaster) {
            case 0:
                gtk_label_set_text(GTK_LABEL(label), "Choose Your Grid !");
                break;
            case 1:
                gtk_label_set_text(GTK_LABEL(label), "CHOOSE YOUR GRID !");
                break;
            case 2:
                gtk_label_set_text(GTK_LABEL(label), "CHOOSE IT !!!!!!");
                break;
            case 3:
                gtk_label_set_text(GTK_LABEL(label), "You know what...");
                break;
            case 4:
                gtk_label_set_text(GTK_LABEL(label), "Just forget about it.");
                break;
            case 5:
                gtk_label_set_text(GTK_LABEL(label), "             ...");
                break;
            }
            cptEaster += cptEaster <= 5;
        }
        else if(lenF > 4) {
            if(valid_format(lenF)) {
                //Call main_Interface
                gtk_label_set_text(GTK_LABEL(label), "Processing...");
                if(main_ImageProcess(file)){
                    gtk_label_set_text(GTK_LABEL(label), "Tadaaaaaa!");
                    gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        "results/step9_Solved.png");
                } else {
                    gtk_label_set_text(GTK_LABEL(label), "No Solution Found !");
                }
            } else {
                gtk_label_set_text(GTK_LABEL(label), ".PNG OR .JPG");
            }
        }
    }
}

int main/*_interface*/ (int argc, char **argv)
{
	gtk_init(&argc, &argv);
    	file = "";
    	cptEaster = 0;

    	builder = gtk_builder_new_from_file("interface.glade");
    	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    	fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    	fileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooser"));
    	button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    	label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    	preview = GTK_WIDGET(gtk_builder_get_object(builder, "preview"));

    	g_signal_connect(window, "destroy",
        	G_CALLBACK(gtk_main_quit), NULL);
    	g_signal_connect(GTK_FILE_CHOOSER(fileChooser), "update-preview",
        	G_CALLBACK (updateImage), NULL);
    	g_signal_connect(GTK_BUTTON(button), "clicked",
        	G_CALLBACK(callOCRProject), NULL);

    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}

