#include "client.h"

int NewMesageID(char chatName[32]) {
   sqlite3_stmt* stmt;
   int n = 0;
   char sql[200];
   bzero(sql, 60);
   strcat(sql, "SELECT MAX(ID) FROM ");
   strncat(sql, chatName, 32);
   strcat(sql, ";");
   printf("SQL: %s", sql);
   sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

   sqlite3_step(stmt);
   printf("NOT DONE\n");
   n = sqlite3_column_int(stmt, 0);

   return n;
}

void CheckMessages() {
   sqlite3_stmt* stmt;
   const unsigned char* _chatName;
   char chatName1[33];
   char sql[43];

   bzero(sql, 43);
   bzero(chatName1, 32);
   strcat(sql, "select chatName from chats");

   sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
   while (sqlite3_step(stmt) != SQLITE_DONE) {
      _chatName = sqlite3_column_text(stmt, 0);

      for (int i = 0; i < 32; i++) {
         chatName1[i] = _chatName[i];
      }

      int ID = NewMesageID(chatName1);

      UPDATEMESSAGES(chatName1, ID);
   }
}

int CheckChat(char chatName[32]) {
   sqlite3_stmt* stmt;
   const unsigned char* _chatName;
   char chatName1[33];
   char sql[43];

   bzero(sql, 43);
   bzero(chatName1, 32);
   strcat(sql, "select chatName from chats");

   sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
   while (sqlite3_step(stmt) != SQLITE_DONE) {
      _chatName = sqlite3_column_text(stmt, 0);

      for (int i = 0; i < 32; i++) {
         chatName1[i] = _chatName[i];
      }

      if(!strncmp(chatName, chatName1, 32)) {
         return 0;
      }
   }
   return 1;
}

void MesageRecieve(char id[], char chatName[32], char text[]) {
   
   char *zErrMsg = 0;
   char sql[1000] = "insert into ";
   strcat(sql, chatName);
   strcat(sql, " VALUES(");
   strncat(sql, id, 4);
   strcat(sql, ", '");
   strncat(sql, text, strlen(text));
   strcat(sql, "');");
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
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "Create chat table: %s\n", zErrMsg);

   }else {
      bzero(sql, 100);
      strcat(sql, "INSERT INTO chats VALUES( '");
      strncat(sql, chatname, 32);
      strcat(sql, "', 1);");
      rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
      if (rc != SQLITE_OK) {
         fprintf(stderr, "Insert into chats: %s\n", zErrMsg);
      }
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

   sql = "CREATE TABLE IF NOT EXISTS chats(chatName varchar, read INT);";
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Created table successfully\n");
   }

   return 0;
}
