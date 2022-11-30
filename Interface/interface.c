#include <gtk/gtk.h>
#include <string.h>

static GtkBuilder* builder;
static GtkWidget* window;
static GtkWidget* fixed;
static GtkWidget* fileChooser;
static GtkWidget* button1;
static GtkWidget* button2;
static GtkWidget* button3;
static GtkWidget* label1;
static GtkWidget* label2;
static GtkWidget* preview;
static char* file;
static int bsolve;
static int stepc;

int valid_format(int len)
{
    	if (file[len-4] == '.' && file[len-3] == 'j'
            && ((file[len-2] == 'p' && file[len-1] == 'g')))
		return 1;

    	if (file[len-5] == '.' && file[len-4] == 'j'
	    && file[len-3] == 'p' && file[len-2] == 'e'
	    && file[len-1] == 'g')
		return 1;
	return 0;
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
            gtk_label_set_text(GTK_LABEL(label1), "Please choose a .pneg or .jpg");
        }
	
        gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*) file);
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
		gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*) "error_image1.jpg");
                break;
            }
            bsolve += bsolve <= 2;
        }
        /*else if(lenF > 4) 
	 {
            	if(valid_format(lenF)) 
	    	{
                
                	gtk_label_set_text(GTK_LABEL(label), "Processing...");
                	if(main_ImageProcess(file))
			{
                    		gtk_label_set_text(GTK_LABEL(label), "Tadaaaaaa!");
                    		gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
                	}
			else 
			{
                    		gtk_label_set_text(GTK_LABEL(label), "No Solution Found !");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
				"error_image2.png");
                	}
            	} 
	    	else 
	    	{
                	gtk_label_set_text(GTK_LABEL(label), ".PNG OR .JPG");
            	}
        }*/
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
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*) "error_image1.jpg");
                		break;
            		}
           	 	bsolve += bsolve <= 2;
        	}
	}
	/*else* if(lenF >4)
	{
		gtk_label_set_text(GTK_LABEL(label1), "Let's gooooooo");
		if(main_ImageProcess(file))
		{
			switch(stepc)
			{
			case 0:
				gtk_label_set_text(GTK_LABEL(label2), "Grayscale");
                    		gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				break;
			case 1:
				gtk_label_set_text(GTK_LABEL(label2), "Binarization -->");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				break;
			case 2:
				gtk_label_set_text(GTK_LABEL(label2), "Sobel Filter -->");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				break;
			case 3:
				gtk_label_set_text(GTK_LABEL(label2), "Hough Transform -->");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				break;
			case 4:
				gtk_label_set_text(GTK_LABEL(label2), "Separate -->");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				break;
			case 5:
				gtk_label_set_text(GTK_LABEL(label2), "Processing -->");

				gtk_label_set_text(GTK_LABEL(label2), "Solution ! -->");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
				gtk_label_set_text(GTK_LABEL(label1), "We did it !");
			}
			stepc += stepc <= 5;
		}
		else
		{
			gtk_label_set_text(GTK_lABEL(label1), "Oh nooooo :'(")
                    	gtk_label_set_text(GTK_LABEL(label2), "No Solution Found !");
			gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
			"error_image2.png");
                }
            } 
	    else
	    {
                gtk_label_set_text(GTK_LABEL(label), ".png OR .jpeg please");
            }
        }
	 */
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
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*) "error_image1.jpg");
                		break;
            		}
           	 	bsolve += bsolve <= 2;
        	}
	}
		/*else* if(lenF >4)
		{
			gtk_label_set_text(GTK_LABEL(label1), "Let's gooooooo");
			if(main_ImageProcess(file))
			{
				switch(stepc)
				{
				case 0:
					gtk_label_set_text(GTK_LABEL(label2), "Grayscale");
                    			gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        		"results/step9_Solved.png");
					break;
				case 1:
					gtk_label_set_text(GTK_LABEL(label2), "Binarization -->");
					gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
        	                	"results/step9_Solved.png");
					break;
				case 2:
					gtk_label_set_text(GTK_LABEL(label2), "Sobel Filter -->");
					gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        		"results/step9_Solved.png");
					break;
				case 3:
					gtk_label_set_text(GTK_LABEL(label2), "Hough Transform -->");
					gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
					break;
				case 4:
					gtk_label_set_text(GTK_LABEL(label2), "Separate -->");
					gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        	"results/step9_Solved.png");
					break;
				case 5:
					gtk_label_set_text(GTK_LABEL(label2), "Processing -->");

					gtk_label_set_text(GTK_LABEL(label2), "Solution ! -->");
					gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
                        		"results/step9_Solved.png");
					gtk_label_set_text(GTK_LABEL(label1), "We did it !");
                
				}
				stepc += stepc <= 5;
			}
			else
			{
				gtk_label_set_text(GTK_lABEL(label1), "Oh nooooo :'(")
                    		gtk_label_set_text(GTK_LABEL(label2), "No Solution Found !");
				gtk_image_set_from_file(GTK_IMAGE(preview), (const gchar*)
				"error_image2.png");
			}
                }
	}
	else
	{
        	gtk_label_set_text(GTK_LABEL(label), ".png OR .jpeg please");
        }
*/
}

int main/*_interface*/ (int argc, char **argv)
{
	gtk_init(&argc, &argv);
    	file = "";
    	bsolve = 0;
	stepc = 0;

    	builder = gtk_builder_new_from_file("interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    	fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    	fileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooser"));
    	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    	preview = GTK_WIDGET(gtk_builder_get_object(builder, "preview"));

    	g_signal_connect(window, "destroy",
        	G_CALLBACK(gtk_main_quit), NULL);
    	g_signal_connect(GTK_FILE_CHOOSER(fileChooser), "update-preview",
        	G_CALLBACK (updateImage), NULL);
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
