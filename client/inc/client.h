#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <gtk/gtk.h>

/*
typedef struct s_chat t_chat;

struct s_chat {
    gint argc;
    char **argv;
    GtkBuilder *builder;
};
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget);
void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible);
*/

#define MX_GUI_PATH "src/gui.glade"


int mx_atoi(const char *str);
bool mx_isdigit(int c);
int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);



// Log in/Registration menu
//==========================================================================================
/*
    GtkWidget *window;
    GtkWidget *maintitle, *label;
    GtkWidget *enter_button, *reg_button;
    GtkWidget *titlebox, *loginbox, *mainbox, *passbox, *enterbox, *reg_menu;
    GtkWidget *login_entry, *pass_entry;

    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    GError *error = 0;
//==========================================================================================
static void authorization(GtkWidget *widget, GdkEvent *event, gpointer *data);

*/



#endif
