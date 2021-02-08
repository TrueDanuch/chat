#include "client.h"

void mx_add_dialog(GtkButton *btn)
{
    gchar *add_member = mx_get_buffer_text("buffer_roomname", builder);
    printf("SUCK\n");
    g_print("input: %s", add_member);
    (void)btn;
}
