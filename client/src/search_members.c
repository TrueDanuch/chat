#include "client.h"

void mx_search_members(GtkButton *btn)
{
    GObject *listbox = gtk_builder_get_object(builder, "listbox_rooms");
    gchar *search_members = mx_get_buffer_text("buffer_members", builder);
    
    GtkListBoxRow  *row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox), 0);

    mx_widget_set_visibility_by_name(builder, "label_search_nothing_local", FALSE);

    GtkWidget *texttest = gtk_label_new(search_members);

    gtk_list_box_select_row(GTK_LIST_BOX(listbox), row);

    gtk_list_box_insert(GTK_LIST_BOX(listbox), texttest, 0);

    gtk_widget_show_all(GTK_WIDGET(listbox));
    (void)btn;
}
