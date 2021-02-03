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
#include <sqlite3.h>
#include <gtk/gtk.h>


#define MX_GUI_PATH "src/gui.glade"
#define MX_ROOM_CTRL 0
#define MX_MSG_CTRL 1
#define MX_IMGS_PATH "img/gui/"
#define MX_IMG_EYE MX_IMGS_PATH "visibility.png"
#define MX_IMG_CLOSEDEYE MX_IMGS_PATH "unvisibility.png"
#define MX_LOCAL_ROOMS "listbox_rooms"
#define MX_GLOBAL_ROOMS "listbox_global_rooms"

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
GtkBuilder *builder;
GtkWidget *wnd_main, *dialog_auth, *window;

sqlite3 *db;
int rc;
pthread_t rd, wr;
int fd;
char logname[17];

//--------------------------------------------------------------------------------------------------
//------------------------------------------   Connection ------------------------------------------
//--------------------------------------------------------------------------------------------------

//utils
int mx_atoi(const char *str);
bool mx_isdigit(int c);

//errproc
int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *src, void *dst);

//Comands
void SendMesage(char chatName[32], char* text);
void NewChatComand(char chatname[32]);
void MessageRecieveComand(char buf[]);

//database
void Decrypt(char buf[], int fd);
int DataBase();
void NewChat(char chatname[32]);
void MesageRecieve(char id, char chatName[32], char text[]);

//--------------------------------------------------------------------------------------------------
//------------------------------------------   GUI  ------------------------------------------------
//--------------------------------------------------------------------------------------------------

typedef struct s_groom t_groom;
typedef struct s_chat t_chat;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkListBox *box_messages;
    GtkLabel *label_name;
    GHashTable *members;
    gboolean is_watched;
    guint64 id;
    char *room_name;
    char *customer;
    guint64 customer_id;
    guint64 date;
    char *desc;
    gboolean is_updated;
    gint uploaded;
    gdouble power;
    gboolean select_all;
    gboolean select_own;
    gboolean select_another;
    gboolean select_notedit;
};

struct s_chat {
    char *auth_token;
    char *login;
    gchar *desc;
    gint argc;
    char **argv;
    gsize id;
    t_groom *curr_room;
    gboolean upl_old_msgs;
    GtkBuilder *builder;
    gboolean valid;
    gboolean msg_placeholder;
    gboolean shift_hold;
};

void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible);
void mx_widget_switch_visibility(GtkWidget *btn, GtkWidget *widget);
void mx_widget_set_visibility_by_name(GtkBuilder *builder, gchar *name, gboolean is_visible);
void mx_search_delim_set_visibility(GtkBuilder *builder, gboolean is_visible);
void mx_set_room_widgets_visibility(GtkBuilder *builder, gboolean visibility);

void mx_switch_room_header(GtkBuilder *builder, gint page_index);
gboolean my_delete_event();
void mx_confirm_login(GtkButton *btn);
void mx_close_auth(GtkButton *btn, GtkDialog *dialog);
void mx_show_password(GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, 
                                                                gpointer *entry_second);
void mx_entry_set_icon_by_path(GtkEntry *entry, gchar *path, GtkEntryIconPosition icon_pos);
t_groom *mx_get_selected_groom(GtkBuilder *builder, gchar *list_name);
void mx_clear_buffer_text(gchar *buff_name, GtkBuilder *builder);
//void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
//void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder);
//void mx_set_unsensetive_confirm(GtkEntryBuffer *buff, guint pos, guint n_chars, GtkEntry *entry);


#endif
