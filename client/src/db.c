#include "client.h"

void MesageRecieve(char id[], char chatName[32], char text[]) {
fprintf(stdout, "STAAAAAARRRTTTTT\n");
   char *zErrMsg = 0;
   char sql[1000] = "insert into ";
fprintf(stdout, "begin strcat\n");
   strcat(sql, chatName);
   strcat(sql, " VALUES(");
   fprintf(stdout, "values\n");
   strncat(sql, id, 4);
   fprintf(stdout, "id\n");
   strcat(sql, ", '");
   strncat(sql, text, strlen(text));
   fprintf(stdout, "text\n");
   strcat(sql, "');");
fprintf(stdout, "finish strcat\n");
   printf("%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Mesage recieved successfully\n");
   }
}

void NewChat(char chatname[32]) {
   char *zErrMsg = 0;
   char sql[100] = "CREATE TABLE ";

   strncat(sql, chatname, 32);
   strcat(sql, "(ID INT, mesage varchar);");
   printf("%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Created chat successfully\n");
   }
}

int DataBase() {
   char *zErrMsg = 0;
   char *sql;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   sql = "CREATE TABLE IF NOT EXISTS chats(catName varchar, read INT);";
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Created table successfully\n");
   }

   return 0;
}
