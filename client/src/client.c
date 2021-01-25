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


int main(int adc, char* adv[]) {

    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init (NULL, NULL);
    GError *err = NULL;

    builder = gtk_builder_new();
    if(0 == gtk_builder_add_from_file(builder, MX_GUI_PATH, &err))
    {
        fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show(window);
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
