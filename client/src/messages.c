#include "client.h"

void mx_send_message(GtkButton *btn)
{
    gchar *message = mx_get_buffer_text("buffer_message", builder);
    GtkWidget *box = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *mesgs = gtk_label_new(message);
    GtkWidget *view = gtk_viewport_new(NULL, NULL);


    printf("SUCK\n");
    gtk_container_add(GTK_CONTAINER(scroll), view);
    gtk_container_add(GTK_CONTAINER(view), box);
    printf("SUCK1\n");
    gtk_container_add(GTK_CONTAINER(box), mesgs);
    printf("SUCK2\n");
    gtk_widget_set_can_focus(box, FALSE);
    printf("SUCK3\n");
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);;
    printf("SUCK4\n");
    gtk_widget_show_all(scroll);
    printf("SUCK5\n");
    gtk_widget_show_all(box);
    (void)btn;
}

