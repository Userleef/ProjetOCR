#include <gtk/gtk.h>
#include <stdlib.h>

GtkWidget *window1;
GtkWidget *window2;
GtkWidget *window3;
GtkWidget *textdisplay;
GtkWidget *Image;
GtkWidget *window4;
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

void openfile(GtkWidget *filechooserbutton)
{
    char *filename =
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
}

void savefile(GtkWidget *filechooserbutton)
{
    char *filename =
        gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooserbutton));
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
