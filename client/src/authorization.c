#include "client.h"

void mx_close_auth(GtkButton *btn, GtkDialog *dialog) 
{
    gtk_widget_destroy(GTK_WIDGET(dialog));
    (void)btn;
}

void mx_confirm_login(GtkButton *btn)
{
    gtk_widget_destroy(GTK_WIDGET(dialog_auth));
    gtk_main_quit();
    gtk_widget_show_all(GTK_WIDGET(wnd_main));
    gtk_main ();
    (void)btn;
    
}

void mx_show_password(GtkEntry *entry, GtkEntryIconPosition icon_pos,
                      GdkEvent *event, gpointer *entry_second) {
    if (gtk_entry_get_visibility(entry)) {
        mx_entry_set_icon_by_path(entry, MX_IMG_EYE, icon_pos);
        gtk_entry_set_visibility(entry, FALSE);
        if (GTK_IS_ENTRY(entry_second))
            gtk_entry_set_visibility(GTK_ENTRY(entry_second), FALSE);
    }
    else { 
        mx_entry_set_icon_by_path(entry, MX_IMG_CLOSEDEYE, icon_pos);
        gtk_entry_set_visibility(entry, TRUE);
        if (GTK_IS_ENTRY(entry_second))
            gtk_entry_set_visibility(GTK_ENTRY(entry_second), TRUE);
    }
    (void)event;
}

void mx_set_sensetive_confirm(GtkEntryBuffer *buff, guint pos, gchar *chars,
                              guint n_chars, GtkEntry *entry) {
    char *buffer = (char*)gtk_entry_buffer_get_text(buff);

    if (strlen(buffer))
        gtk_widget_set_sensitive(GTK_WIDGET(entry), 1);
    (void)buff;
    (void)pos;
    (void)chars;
    (void)n_chars;
}
