#include "client.h"

void* Write(void* FD) {
    int fd = *(int *) FD;
    char buf[1024];
    int n;
    while(1) {
        bzero(buf, sizeof(buf));
        n = 0;
        while((buf[n++] = getchar()) != '\n');
        send(fd, buf, sizeof(buf), 0);
        pthread_testcancel();
    }
    pthread_exit(NULL);
}
void* Read(void* FD) {
    int fd = * (int *) FD;
    char buf[1024];
    while(1) {
        if (recv(fd, buf, 1024, 0) > 0) {
            printf("Read: %s", buf);
            bzero(buf, sizeof(buf));
        }
        else {
            printf("You are disconnected!\n");
            break;
        }
    }
    pthread_exit(NULL);
}

/*
GtkBuilder *mx_init_window(gint argc, char **argv) {
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_connect_signals(builder, builder);
    return builder;
}

void mx_start_main_window(t_chat *chat) {
    GObject *wnd_main = gtk_builder_get_object(chat->builder, "wnd_main");
    GObject *dialog_auth = gtk_builder_get_object(chat->builder, "dialog_auth");
    mx_widget_switch_visibility(NULL, GTK_WIDGET(dialog_auth));
    mx_widget_switch_visibility(NULL, GTK_WIDGET(wnd_main));
}
void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible) {
    if (is_visible)
        gtk_widget_show(widget);
    else
        gtk_widget_hide(widget);    
}
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget) {
    mx_widget_set_visibility(widget, !gtk_widget_is_visible(widget));
    (void)usr_ctrl;
}
*/

static GtkWidget*
create_window (void)
{
        /* это виджет окна */
        GtkWidget *window;
        /* это тот волшебный объект, который сделает за нас окошко */
        GtkBuilder *builder;
        /* сюда будем складывать ошибки */
        GError* error = NULL;

        /* тут загружаем файл с интерфейсом */
        builder = gtk_builder_new ();
        if (!gtk_builder_add_from_file (builder, "gui.glade", &error))
        {
                /* загрузить файл не удалось */
                g_critical ("Не могу загрузить файл: %s", error->message);
                g_error_free (error);
        }

        /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
        gtk_builder_connect_signals (builder, NULL);

        /* получаем виджет окна, чтобы его показать */
        window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
        if (!window)
        {
                /* что-то не так, наверное, ошиблись в имени */
                g_critical ("Ошибка при получении виджета окна");
        }
        g_object_unref (builder);

        return window;
}


int main(int adc, char* adv[]) {
    //t_chat *chat = NULL;
    //mx_start_main_window(chat);
    /* виджет окна */
    GtkWidget *window;

    /* запускаем GTK+ */
    gtk_init (NULL, NULL);

    /* вызываем нашу функцию для создания окна */
    window = create_window ();
    gtk_widget_show (window);

    /* передаём управление GTK+ */
    gtk_main ();

    adc = 1;
    pthread_t rd, wr;
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
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
    pthread_join(rd, NULL);
    pthread_cancel(wr);
    close(fd);
    return 0;
}
