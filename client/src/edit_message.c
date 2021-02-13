#include "client.h"

void mx_edit_msg()
{
    GObject *messages = gtk_builder_get_object(builder, "listbox_found_msgs");

    GObject *btn_edit_msg_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send_msg = gtk_builder_get_object(builder, "btn_send_msg");
    GObject *btn_edit_msg_cancel = gtk_builder_get_object(builder, "btn_edit_msg_cancel");
    GObject *btn_del_msg = gtk_builder_get_object(builder, "btn_del_msg");

    GObject *buf_message = gtk_builder_get_object(builder, "buffer_message");
    GtkWidget *mesg_row = GTK_WIDGET(gtk_list_box_get_selected_row(GTK_LIST_BOX(messages)));
    if(gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(mesg_row)))
    {
        int numbers = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(mesg_row));
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(mesg_row));
        printf("Output: %s\n", gtk_label_get_label(GTK_LABEL(child)));
        printf("Output: %d\n", numbers);
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buf_message), gtk_label_get_label(GTK_LABEL(child)), -1);
        printf("Suck\n");
        gtk_widget_show(GTK_WIDGET(btn_edit_msg_apply));
        gtk_widget_show(GTK_WIDGET(btn_edit_msg_cancel));
        gtk_widget_hide(GTK_WIDGET(btn_send_msg));
        gtk_widget_hide(GTK_WIDGET(btn_del_msg));
    }
    else
    {
        printf("Fuck\n");
    }
    (void)buf_message;
}

void mx_clear_msg_edit()
{
    GObject *messages = gtk_builder_get_object(builder, "listbox_found_msgs");
    GObject *buf_message = gtk_builder_get_object(builder, "buffer_message");
    GtkWidget *mesg_row = GTK_WIDGET(gtk_list_box_get_selected_row(GTK_LIST_BOX(messages)));

    GObject *btn_edit_msg_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send_msg = gtk_builder_get_object(builder, "btn_send_msg");
    GObject *btn_edit_msg_cancel = gtk_builder_get_object(builder, "btn_edit_msg_cancel");
    GObject *btn_del_msg = gtk_builder_get_object(builder, "btn_del_msg");

    gtk_list_box_unselect_row(GTK_LIST_BOX(messages), GTK_LIST_BOX_ROW(mesg_row));

    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buf_message), "", 0);

    gtk_widget_hide(GTK_WIDGET(btn_edit_msg_apply));
    gtk_widget_hide(GTK_WIDGET(btn_edit_msg_cancel));
    gtk_widget_show(GTK_WIDGET(btn_send_msg));
    gtk_widget_show(GTK_WIDGET(btn_del_msg));
}

void mx_edit_msg_send()
{
    GObject *messages = gtk_builder_get_object(builder, "listbox_found_msgs");
    GObject *buf_message = gtk_builder_get_object(builder, "buffer_message");
    gchar *message_text = mx_get_buffer_text("buffer_message", builder);
    GtkListBoxRow *mesg_row = gtk_list_box_get_selected_row(GTK_LIST_BOX(messages));

    GObject *btn_edit_msg_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send_msg = gtk_builder_get_object(builder, "btn_send_msg");
    GObject *btn_edit_msg_cancel = gtk_builder_get_object(builder, "btn_edit_msg_cancel");
    GObject *btn_del_msg = gtk_builder_get_object(builder, "btn_del_msg");

    if(gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(mesg_row)))
    {
        int numbers = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(mesg_row));
        printf("Output: %d\n", numbers);
        char* mesg = message_text;
        GtkWidget *child = gtk_bin_get_child(GTK_BIN(mesg_row));
        printf("Outputssss: %s\n", gtk_label_get_label(GTK_LABEL(child)));

        gtk_label_set_text(GTK_LABEL(child), mesg);

        gtk_widget_show_all(GTK_WIDGET(messages));
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buf_message), "", 0);
    }
    gtk_widget_hide(GTK_WIDGET(btn_edit_msg_apply));
    gtk_widget_hide(GTK_WIDGET(btn_edit_msg_cancel));
    gtk_widget_show(GTK_WIDGET(btn_send_msg));
    gtk_widget_show(GTK_WIDGET(btn_del_msg));

}
