#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include "../Solver/main.h"
#include "../Saved/main.h"
#include "../Rotate/main.h"
#include "../Load_img/main.h"

static GtkBuilder* builder;
static GtkWidget* window;
static GtkWidget* fixed;
static GtkWidget* fileChooser;
static GdkPixbuf* pixbuf_2;
static GtkWidget* button1;
static GtkWidget* button2;
static GtkWidget* button3;
static GtkWidget* button4;
static GtkWidget* label1;
static GtkWidget* label2;
static GtkWidget* preview;
static GtkScale* scale;
static GtkEntry* entry;
static char* file;
static int bsolve;
static int stepc;

int valid_format(int len)
{
    	if (file[len-4] == '.' && file[len-3] == 'j'
            && ((file[len-2] == 'p' && file[len-1] == 'g')))
		return 1;

    	if (file[len-4] == '.' && file[len-3] == 'p'
	    && file[len-2] == 'n' && file[len-1] == 'g')
		return 1;
	return 0;
}

GdkPixbuf* resize(char *file)
{
	
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(file,NULL);
	pixbuf_2 = gdk_pixbuf_scale_simple(pixbuf,775,750, GDK_INTERP_NEAREST);
	gtk_image_set_from_pixbuf(GTK_IMAGE(preview), pixbuf_2);
	return pixbuf_2;
}

void updateImage(GtkFileChooser *fc)
{
    file = gtk_file_chooser_get_preview_filename(fc);
    if(file)
    {
        if(valid_format(strlen(file)))
	{
            gtk_label_set_text(GTK_LABEL(label1), "THE FORMAT IS VALID !");
        }
       	else 
	{
            gtk_label_set_text(GTK_LABEL(label1), "Please choose a .png or .jpg");
        }
	pixbuf_2 = resize(file);
	gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
    }
}

void quickOCR()
{
	gtk_widget_set_sensitive(GTK_WIDGET(button4), FALSE);
    if(file)
    {
        size_t lenF = strlen(file);
        if(lenF == 0) 
	{
            switch(bsolve) 
	    {
            case 0:
                gtk_label_set_text(GTK_LABEL(label1), "Choose Your Grid !");
                break;
            case 1:
                gtk_label_set_text(GTK_LABEL(label1), "CHOOSE YOUR GRID !");
                break;
            case 2:
                gtk_label_set_text(GTK_LABEL(label1), "CHOOSE IT !!!!!!");
				pixbuf_2 = resize("error_image1.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
                break;
            }
            bsolve += bsolve <= 2;
        }
        else if(lenF > 4) 
		{
            if(valid_format(lenF)) 
	    	{
                
				gtk_label_set_text(GTK_LABEL(label1), "Processing...");
				if(ocr_2(file, stepc))
				{
					switch (stepc)
					{
					case 0:
						gtk_label_set_text(GTK_LABEL(label2), "Ocr -->");
						pixbuf_2 = resize("saved_ocr.png");
						gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
						gtk_label_set_text(GTK_LABEL(label2), "Enter X Y Value !");
						break;
					
					case 1:
						gtk_label_set_text(GTK_LABEL(label2), "Tadaaaaaa!");
						gtk_label_set_text(GTK_LABEL(label1), "THERE IT IS !");
						pixbuf_2 = resize("saved.png");
						gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
						break;

					default:
						break;
					}
					stepc += stepc <= 1;

				}
				else 
				{
					gtk_label_set_text(GTK_LABEL(label1), "No Solution Found !");
					pixbuf_2 = resize("error_image1.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
				}
            } 
	    	else 
	    	{
            	gtk_label_set_text(GTK_LABEL(label1), ".PNG OR .JPG PLEASE");
            }
        }
    }
}

void step_click_OCR()
{
	gtk_widget_set_sensitive(GTK_WIDGET(button4), FALSE);
	if(file)
    	{
        	size_t lenF = strlen(file);
        	if(lenF == 0) 
		{
            		switch(bsolve) 
	    		{
            		case 0:
                		gtk_label_set_text(GTK_LABEL(label1), "Choose Your Grid !");
                		break;
            		case 1:
                		gtk_label_set_text(GTK_LABEL(label1), "CHOOSE YOUR GRID !");
                		break;
            		case 2:
                		gtk_label_set_text(GTK_LABEL(label1), "CHOOSE IT !!!!!!");
						pixbuf_2 = resize("error_image1.jpg");
						gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
                		break;
            		}
           	 	bsolve += bsolve <= 2;
        	}
		else if(lenF >4)
		{
			gtk_label_set_text(GTK_LABEL(label1), "Let's gooooooo");
			if(ocr(file,stepc))
			{
				switch(stepc)
				{
				case 0:

					gtk_label_set_text(GTK_LABEL(label2), "Grayscale -->");
					pixbuf_2 = resize("grayscale.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 1:

					gtk_label_set_text(GTK_LABEL(label2), "Sobel Filter -->");
					pixbuf_2 = resize("sobel_filter.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 2:

					gtk_label_set_text(GTK_LABEL(label2), "Hough Transform -->");
					pixbuf_2 = resize("hough.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				
				case 3:

					gtk_label_set_text(GTK_LABEL(label2), "Separate -->");
					pixbuf_2 = resize("grid.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					gtk_widget_set_sensitive(GTK_WIDGET(button4), TRUE);
					break;
				case 4:
			
					gtk_label_set_text(GTK_LABEL(label2), "Ocr -->");
					pixbuf_2 = resize("saved_ocr.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					gtk_label_set_text(GTK_LABEL(label2), "Enter X Y Value !");

					break;
				case 5:
					gtk_label_set_text(GTK_LABEL(label2), "Processing -->");
					gtk_label_set_text(GTK_LABEL(label2), "Solution ! -->");
					pixbuf_2 = resize("saved.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					gtk_label_set_text(GTK_LABEL(label1), "We did it !");
					break;
				}
			}
			stepc += stepc <= 5;
		}
		else
		{
			gtk_label_set_text(GTK_LABEL(label1), "Oh nooooo :'(");
                    	gtk_label_set_text(GTK_LABEL(label2), "No Solution Found !");
			pixbuf_2 = resize("error_image1.jpg");
			gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

                }
	} 
	else
	{
		gtk_label_set_text(GTK_LABEL(label1), ".PNG OR .JPG PLEASE");
        }
	 
}

;
int rotate_i()
{
	char* path = gtk_file_chooser_get_preview_filename(fileChooser);
	double value = gtk_range_get_value(GTK_RANGE(scale));
	main_rotate(path,round(value));
	pixbuf_2 = resize("rotate.png");
	gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
	return 1;
}

int modify()
{
	char sudo[9][9] = 
	{
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'},
    	{'.','.','.','.','.','.','.','.','.'}
	};
	FILE *input_file = fopen("./grid.txt", "r");
    	unsigned int i = 0;
    	unsigned int j = 0;
    	char c;
    
   	while((c=fgetc(input_file)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
				sudo[i][j] = c;
				j++;

				if(j > 8)
				{
					j = 0;
					i++;
			}
		}
	}
    fclose(input_file);


	gchar *data = gtk_entry_get_text(GTK_ENTRY(entry));
	int a = data[0] - 48;
	int b = data[2] - 48;
	char value = data[4];
	sudo[a][b] = value;

	FILE* output_file = fopen("./grid.txt", "w");
    printf("test\n");
	for(unsigned int i = 0; i < 9; i++)
	{
		if(i%3 == 0 && i != 0)
			{
				fprintf(output_file, "\n");
			}

		for(unsigned int j = 0; j < 9; j++)
		{
			if(j%3 == 0 && j != 0)
			{
				fprintf(output_file, " ");
			}
			printf("sudo: %c\n", sudo[i][j]);
			fprintf(output_file, "%c", sudo[i][j]);
	}

	fprintf(output_file, "\n");
    }

    fprintf(output_file, "\n");
    fclose(output_file);
    // Redraw for display
	main_save_ocr("./grid.txt");
    pixbuf_2 = resize("./saved_ocr.png");
	gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

	return 1;

}

int main_interface(int argc, char **argv)
{
	gtk_widget_set_sensitive(GTK_WIDGET(button2), FALSE);

	gtk_init(&argc, &argv);
    	file = "";
    	bsolve = 0;
	stepc = 0;
	
    	builder = gtk_builder_new_from_file("interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    	fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    	fileChooser = GTK_WIDGET(gtk_builder_get_object(builder,
			       	"fileChooser"));
    	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    	preview = GTK_WIDGET(gtk_builder_get_object(builder, "preview"));
	scale = GTK_SCALE(gtk_builder_get_object(builder, "scale"));
	entry = GTK_ENTRY(gtk_builder_get_object(builder, "entry"));

	

    	GtkCssProvider* cssProvider = gtk_css_provider_new();
    	gtk_css_provider_load_from_path(cssProvider, "./Interface/style.css",
		       	NULL);

    	GdkScreen* screen = gdk_screen_get_default();
    	gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    	g_signal_connect(window, "destroy",
        	G_CALLBACK(gtk_main_quit), NULL);
    	g_signal_connect(GTK_FILE_CHOOSER(fileChooser), "update-preview",
        	G_CALLBACK (updateImage), NULL);
	gtk_range_set_range(GTK_RANGE(scale), -180, 180);
    	gtk_range_set_value(GTK_RANGE(scale),0);
	g_signal_connect(GTK_BUTTON(button4),"clicked",
		G_CALLBACK(rotate_i),NULL);
    	g_signal_connect(GTK_BUTTON(button1), "clicked",
        	G_CALLBACK(quickOCR), NULL);
	g_signal_connect(GTK_BUTTON(button3),"clicked",
		G_CALLBACK(step_click_OCR), NULL);
	g_signal_connect(GTK_BUTTON(button2),"clicked",
		G_CALLBACK(modify), NULL);

    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}
