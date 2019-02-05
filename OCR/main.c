#include "main.h"


GtkWidget *window1;
GtkWidget *window2;
GtkWidget *window3;
GtkWidget *textdisplay;
GtkWidget *Image;
GtkWidget *window4;

SDL_Surface* surface;

int main(int argc,char **argv)
{

    GtkBuilder      *builder;


    gtk_init(&argc, &argv);


    builder = gtk_builder_new();

    gtk_builder_add_from_file (builder, "interface.glade", NULL);

    window1 = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    gtk_builder_connect_signals(builder, NULL);
    window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
    window3 = GTK_WIDGET(gtk_builder_get_object(builder, "window3"));
    window4 = GTK_WIDGET(gtk_builder_get_object(builder, "window4"));
    textdisplay = GTK_WIDGET(gtk_builder_get_object(builder, "textdisplay"));

    
  
    g_object_unref(builder);

    gtk_widget_show(window4);
    gtk_main();
 

    return 0;
}

void take_image(char *filename)
{ // Load image and treat it

  //char path[30] = "./Image_Test/Jeremie.png";
  surface = IMG_Load(filename);

  grayScale(surface);
  binaryColor(surface);
  //display(surface);
  lineCut(surface);
  //display(surface);
  charcut(surface);
  //display(surface);
}

void openfile(GtkWidget *filechooserbutton)
{ 
    char *filename =
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
    take_image(filename);
}


void begin()
{
    gtk_widget_show(window1);
    gtk_widget_hide(window4);
    gtk_widget_hide(window2);
    gtk_widget_hide(window3);

}
void help()
{
    gtk_widget_show(window3);
    gtk_widget_hide(window1);
    gtk_widget_hide(window2);
    gtk_widget_hide(window4);
}
 

void return_home()
{
    gtk_widget_show(window1);
    gtk_widget_hide(window2);
    gtk_widget_hide(window3);
    gtk_widget_hide(window4);
}

void result()
{
  char * result = isolateChar(surface);
/*
  printf("!!!Result :\n");
  printf("%s", result);
  printf("\n");*/

  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textdisplay));
  GtkTextIter iter;
  gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);
  gtk_text_buffer_insert(buffer, &iter, result, -1);

    gtk_widget_show(window2);
    gtk_widget_hide(window1);
    gtk_widget_hide(window3);
    gtk_widget_hide(window4);
}
void destroy()
{
    gtk_main_quit();
}

void on_Quit_clicked()
{
    destroy();
}

void learn()
{
  size_t lH = 66;
  float p = 0.2f;

  size_t len = 784;
  init_char();
  init_network(len, lH, 62, p);
  Training(850, len);
}