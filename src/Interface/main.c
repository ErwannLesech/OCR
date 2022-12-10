#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "ocr.h"
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
                	if(ocr(file))
			{
                    		gtk_label_set_text(GTK_LABEL(label2), "Tadaaaaaa!");
				gtk_label_set_text(GTK_LABEL(label1), "THERE IT IS !");
                    		pixbuf_2 = resize("saved.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

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
			if(ocr(file))
			{
				switch(stepc)
				{
				case 0:
					printf("0");
					gtk_label_set_text(GTK_LABEL(label2), "Grayscale -->");
					pixbuf_2 = resize("grayscale.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 1:
					printf("0");

					gtk_label_set_text(GTK_LABEL(label2), "Binarization -->");
					pixbuf_2 = resize("image_otsu.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 2:
					printf("0");

					gtk_label_set_text(GTK_LABEL(label2), "Sobel Filter -->");
					pixbuf_2 = resize("sobel_filter.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 3:
					printf("0");

					gtk_label_set_text(GTK_LABEL(label2), "Hough Transform -->");
					pixbuf_2 = resize("hough.png");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				
				case 4:
					printf("0");

					gtk_label_set_text(GTK_LABEL(label2), "Separate -->");
					pixbuf_2 = resize("grid.bmp");
					gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					break;
				case 5:
					printf("0");

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

void step_OCR()
{
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
			if(ocr(file))
			{
				/*gtk_label_set_text(GTK_LABEL(label2), "Grayscale");
                    		pixbuf_2 = resize("grayscale.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

				gtk_label_set_text(GTK_LABEL(label2), "Binarization -->");
				//pixbuf_2 = resize("hough.png");
				//gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
				
				gtk_label_set_text(GTK_LABEL(label2), "Sobel Filter -->");
				pixbuf_2 = resize("sobel_filter.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

				gtk_label_set_text(GTK_LABEL(label2), "Hough Transform -->");
				pixbuf_2 = resize("hough.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
					
				gtk_label_set_text(GTK_LABEL(label2), "Separate -->");
				pixbuf_2 = resize("grid.bmp");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

				gtk_label_set_text(GTK_LABEL(label2), "Processing -->");

				gtk_label_set_text(GTK_LABEL(label2), "Solution ! -->");
				pixbuf_2 = resize("saved.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
				gtk_label_set_text(GTK_LABEL(label1), "We did it !");*/
			
			}
			else
			{
				gtk_label_set_text(GTK_LABEL(label1), "Oh nooooo :'(");
                    		gtk_label_set_text(GTK_LABEL(label2), "No Solution Found !");
				pixbuf_2 = resize("../Load_img/hough.png");
				gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);

			}
                }
	}
	else
	{
        	gtk_label_set_text(GTK_LABEL(label1), ".PNG OR .JPG PLEASE");
        }
}

int rotate_i()
{
	char* path = gtk_file_chooser_get_preview_filename(fileChooser);
	double value = gtk_range_get_value(GTK_RANGE(scale));
	main_rotate(path,round(value));
	pixbuf_2 = resize("rotate.png");
	gtk_image_set_from_pixbuf(GTK_IMAGE(preview),pixbuf_2);
	return 1;
}

int main_interface(int argc, char **argv)
{
	gtk_init(&argc, &argv);
    	file = "";
    	bsolve = 0;
	stepc = 0;
	
    	builder = gtk_builder_new_from_file("interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	//gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &(GdkColor) {1,1,1,1});
    	fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    	fileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooser"));
    	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    	preview = GTK_WIDGET(gtk_builder_get_object(builder, "preview"));
	scale = GTK_SCALE(gtk_builder_get_object(builder, "scale"));
	

    	GtkCssProvider* cssProvider = gtk_css_provider_new();
    	gtk_css_provider_load_from_path(cssProvider, "./Interface/style.css", NULL);

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
	g_signal_connect(GTK_BUTTON(button2),"clicked",
		G_CALLBACK(step_OCR),NULL);
	g_signal_connect(GTK_BUTTON(button3),"clicked",
		G_CALLBACK(step_click_OCR), NULL);

    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}
