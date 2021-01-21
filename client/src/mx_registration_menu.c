#include "../inc/client.h"

gboolean my_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_main_quit();
    printf("Programm closed\n");

    return FALSE;
}

static void load_css(void)//   Connecting CSS file
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    const gchar *css_style_file = "../css/registration_menu.css";
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(provider, css_style_file, NULL);

    g_object_unref(provider);
}

int main (void)
{

    GtkWidget *window;
    GtkWidget *maintitle;
    GtkWidget *titlebox, *loginbox, *mainbox, *passbox;
    GtkWidget *login_entry, *pass_entry;
    const gchar* const title = "♂CUM ZONE♂";

    gtk_init (NULL, NULL);

    load_css();
    ///***      Main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    ///***
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(my_delete_event), NULL);
    ///***      Main Title
    maintitle = gtk_label_new("♂CUM ZONE♂");
    gtk_widget_set_name(maintitle, "chat_name");
    ///***      EntryBar
    login_entry = gtk_entry_new();
    pass_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_entry), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(login_entry), 16);
    gtk_entry_set_placeholder_text(GTK_ENTRY(pass_entry), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(pass_entry), 16);
    ///***      Boxes
    titlebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    loginbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    passbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_name(mainbox, "authorization");
    ///***      Box Structure
    gtk_box_pack_start(GTK_BOX(titlebox), maintitle, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(loginbox), login_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(passbox), pass_entry, TRUE, FALSE, 5);
    ///***
    gtk_box_pack_start(GTK_BOX(mainbox), titlebox, FALSE, FALSE, 100);
    gtk_box_pack_start(GTK_BOX(mainbox), loginbox, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(mainbox), passbox, FALSE, FALSE, 0);
    ///***
    gtk_container_add(GTK_CONTAINER(window), mainbox);



    gtk_widget_show_all(window);
    gtk_main();
}