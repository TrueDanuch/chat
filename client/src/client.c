#include "client.h"

//--------------------------------------------------------------------------------------------------
//------------------------------------------   Connection ------------------------------------------
//--------------------------------------------------------------------------------------------------

void* Write(void* FD) {
    int fld = *(int *) FD;
    fld = 1;
    char chatname[32] = "Andrew__________Dangeonmaster___";
    

    char buf[1024];
    int n;

    while(1) {
        bzero(buf, sizeof(buf));
        n = 0;

        while((buf[n++] = getchar()) != '\n');

        if (buf[0] == '!')
            SendMesage(chatname, buf);
        else 
        send(fd, buf, sizeof(buf), 0);

        pthread_testcancel();
    }
    
    pthread_exit(NULL);
}

void* Read(void* FD) {
    int fd = * (int *) FD;
    char buf[1100];
    while(1) {
        if (recv(fd, buf, 1100, 0) > 0) {
            printf("Reag: %s\n", buf);
            Decrypt(buf, fd);
            bzero(buf, sizeof(buf));
        }
        else {
            printf("You are disconnected!\n");
            break;
        }
    }
    pthread_exit(NULL);
}

//--------------------------------------------------------------------------------------------------
//------------------------------------------   Load CSS  -------------------------------------------
//--------------------------------------------------------------------------------------------------

static void load_css(void)//   Connecting CSS file
{
    const gchar *css_style_file = "../client/css/theme.css";

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(provider, css_style_file, NULL);

    g_object_unref(provider);
}

//--------------------------------------------------------------------------------------------------
//-------------------------------   Connect glade and create window   ------------------------------
//--------------------------------------------------------------------------------------------------

static GtkWidget* create_window (void)
{
    GError* error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, MX_GUI_PATH, &error))
    {
             g_critical ("Не могу загрузить файл: %s", error->message);
             g_error_free (error);
    }
    gtk_builder_connect_signals (builder, builder);
    
    wnd_main = GTK_WIDGET (gtk_builder_get_object (builder, "wnd_main"));
    dialog_auth = GTK_WIDGET(gtk_builder_get_object(builder, "dialog_auth"));
    //g_object_unref (builder);
    gtk_widget_hide(wnd_main);

    
    if (!dialog_auth)
    {
            g_critical ("Ошибка при получении виджета окна");
    }
    
    if (!wnd_main)
    {
            g_critical ("Ошибка при получении виджета окна");
    }

    return dialog_auth;
}

//--------------------------------------------------------------------------------------------------
//-----------------------------------------   Events   ---------------------------------------------
//--------------------------------------------------------------------------------------------------

gboolean my_delete_event()
{
    write(fd, "quit", strlen("quit"));
    pthread_join(rd, NULL);
    pthread_cancel(wr);
    close(fd);
    gtk_main_quit();
    printf("Programm closed\n");
    return FALSE;
}

/*
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder) 
{
    mx_clear_buffer_text("buffer_roomname", builder);
    (void)btn;
}
*/

/*
void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder) 
{
    GObject *box_editing = gtk_builder_get_object(builder, "box_editing_msg");
    GObject *btn_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send = gtk_builder_get_object(builder, "btn_send_msg");

    gtk_widget_hide(GTK_WIDGET(box_editing));
    gtk_widget_hide(GTK_WIDGET(btn_apply));
    gtk_widget_show(GTK_WIDGET(btn_send));;
    mx_clear_buffer_text("buffer_message", builder);
    (void)btn;
}
*/

/*
void mx_switch_to_msg_ctrl(GtkButton *btn, GtkBuilder *builder) 
{
    mx_switch_room_header(builder, MX_MSG_CTRL);
    (void)btn;
}
*/

/*
void mx_set_unsensetive_confirm(GtkEntryBuffer *buff, guint pos, guint n_chars, GtkEntry *entry) 
{
    char *buffer = (char*)gtk_entry_buffer_get_text(buff);

    if (strlen(buffer) == 0)
        gtk_widget_set_sensitive(GTK_WIDGET(entry), 0);
    (void)buff;
    (void)pos;
    (void)n_chars;
}
*/

//--------------------------------------------------------------------------------------------------
//-------------------------------------   Main Function   ------------------------------------------
//--------------------------------------------------------------------------------------------------

int main(int adc, char* adv[]) 
{

    gtk_init (NULL, NULL);
    load_css();
    window = create_window ();
    gtk_widget_show_all(window);

    DataBase();
    strncat(logname, "Andrew          ", 16);
    adc = 1;
    sginInt = -1;
    regInt = 0;
    pthread_t rd;
    pthread_t wr;
    fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(adv[2]));
    adr.sin_addr.s_addr = inet_addr(adv[1]);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    char buf[1024];
    recv(fd, &buf, sizeof(buf), 0);
    printf("Server: %s",buf);
    pthread_create(&rd, NULL, Read, &fd);
    pthread_create(&wr, NULL, Write, &fd);

    gtk_main ();
    
    return 0;
}
