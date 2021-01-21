#include "../inc/client.h"

static void authorization(GtkWidget *widget, GdkEvent *event, gpointer *data)
{
    gtk_widget_hide(GTK_WIDGET(mainbox));
    reg_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(mainbox), reg_menu, FALSE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(reg_menu), 600, 600);
    gtk_widget_set_name(GTK_WIDGET(reg_menu), "Reg");
}

gboolean my_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_main_quit();
    printf("Programm closed\n");

    return FALSE;
    
}

static void load_css(void)//   Connecting CSS file
{
    const gchar *css_style_file = "../css/registration_menu.css";

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(provider, css_style_file, NULL);

    g_object_unref(provider);
}

int main (void)
{

    gtk_init (NULL, NULL);

    load_css();
    ///***      Authorization window
    const gchar* const title = "♂CUM ZONE♂";
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 1024, 768);
    //gtk_window_set_default_icon_from_file("../img/main_icon.png", NULL);
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    /*
    label = gtk_label_new (NULL);
    gtk_box_pack_start (GTK_BOX (mainbox), label, FALSE, FALSE, 0);
    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
    gtk_widget_set_halign (frame, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (frame, GTK_ALIGN_CENTER);
    gtk_box_pack_start (GTK_BOX (mainbox), frame, FALSE, FALSE, 0);

    image = gtk_image_new_from_resource ("../img/tenor.gif");
    
    gtk_container_add (GTK_CONTAINER (frame), image);
    */

    ///***
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(my_delete_event), NULL);
    ///***      Main Title
    maintitle = gtk_label_new("");
    gtk_widget_set_name(maintitle, "chat_name");
    ///***      EntryBar
    login_entry = gtk_entry_new();
    pass_entry = gtk_entry_new();
    enter_button = gtk_button_new_with_label("Enter");
    reg_button = gtk_button_new_with_label("Sign Up");
    g_signal_connect(G_OBJECT(reg_button), "button_press_event", G_CALLBACK(authorization), NULL);
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_entry), "Login:");
    gtk_entry_set_max_length(GTK_ENTRY(login_entry), 16);
    gtk_entry_set_placeholder_text(GTK_ENTRY(pass_entry), "Password:");
    gtk_entry_set_max_length(GTK_ENTRY(pass_entry), 16);
    gtk_entry_set_visibility(GTK_ENTRY(pass_entry), FALSE);
    ///***      Boxes
    mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    titlebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    loginbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    passbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    enterbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    ///***
    gtk_widget_set_size_request(GTK_WIDGET(mainbox), 500, 500);
    gtk_widget_set_name(GTK_WIDGET(mainbox), "authorization");
    gtk_widget_set_valign(GTK_WIDGET(mainbox), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(mainbox), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(enterbox), GTK_ALIGN_CENTER);
    gtk_widget_set_halign(GTK_WIDGET(enterbox), GTK_ALIGN_CENTER);
    ///***
    gtk_widget_set_size_request(GTK_WIDGET(login_entry), 300, 30);
    gtk_widget_set_size_request(GTK_WIDGET(pass_entry), 300, 30);
    gtk_widget_set_size_request(GTK_WIDGET(enter_button), 140, 40);
    gtk_widget_set_size_request(GTK_WIDGET(reg_button), 140, 40);
    ///***      Box Structure
    gtk_box_pack_start(GTK_BOX(titlebox), maintitle, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(loginbox), login_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(passbox), pass_entry, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(enterbox), enter_button, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(enterbox), reg_button, FALSE, FALSE, 5);
    gtk_box_set_spacing(GTK_BOX(enterbox), 10);
    ///***

    gtk_box_pack_start(GTK_BOX(mainbox), titlebox, FALSE, FALSE, 70);
    gtk_box_pack_start(GTK_BOX(mainbox), loginbox, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(mainbox), passbox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(mainbox), enterbox, FALSE, FALSE, 30);
    ///***
    gtk_container_add(GTK_CONTAINER(window), mainbox);

    //=================================================================================

    // Registration menu 
    //=================================================================================
    


    gtk_widget_show_all(window);
    gtk_main();
}