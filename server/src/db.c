#include "server.h"

int NewMesageID(char chatName[32]) {
   sqlite3_stmt* stmt;
   int n = 0;
   char sql[200];
   bzero(sql, 60);
   strcat(sql, "SELECT * FROM ");
   strncat(sql, chatName, 32);
   strcat(sql, " WHERE ID=(SELECT max(ID) FROM ");
   strncat(sql, chatName, 32);
   strcat(sql, ");");

   sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

   if (sqlite3_step(stmt) != SQLITE_DONE) {
      printf("NOT DONE\n");
      n = sqlite3_column_int(stmt, 0);
   }
   else {
      printf("DONE\n");
   }

   return n;
}

void NewMesage(char chatName[32], char text[]) {
   char* zErrMsg = 0;
   char sql[1056] = "insert into ";
   int id;
   id = NewMesageID(chatName) + 1;

   strncat(sql, addX(chatName), 32);
   strcat(sql, " VALUES( ");
   strcat(sql, mx_itoa(id));
   strcat(sql, ", '");
   strncat(sql, text, strlen(text));
   strcat(sql, "');");
   fprintf(stderr, "%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "INSERT ERROR: %s\n", zErrMsg);
   }

   bzero(sql, 1056);
   strcat(sql, "select ID, mesage from ");
   strncat(sql, chatName, 32);
   sqlite3_stmt* stmt;
   sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
   const unsigned char* mesg;

   while (sqlite3_step(stmt) != SQLITE_DONE) {
      id = sqlite3_column_int(stmt, 0);
      mesg = sqlite3_column_text(stmt, 1);
      
      fprintf(stdout, "%d: %s", id, mesg);
   }
}

void NewChat(char name1[16], char name2[16]) {
   char* zErrMsg = 0;
   
   //add name of chat to the table for the first user
   char sql[100] = "insert into ";
   strncat(sql, addX(name1), 16);
   strcat(sql, " VALUES('");
   strncat(sql, addX(name1), 16);
   strncat(sql, addX(name2), 16);
   strcat(sql, "', 1);");
   fprintf(stderr, "%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "INSERT ERROR: %s\n", zErrMsg);
   }

   //add name of chat to the table for the second user
   strcpy(sql, "insert into ");
   strncat(sql, addX(name2), 16);
   strcat(sql, " VALUES('");
   strncat(sql, addX(name1), 16);
   strncat(sql, addX(name2), 16);
   strcat(sql, "', 1);");
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "INSERT ERROR: %s\n", zErrMsg);
   }

   //create table for chat
   strcpy(sql, "CREATE TABLE IF NOT EXISTS ");
   strncat(sql, addX(name1), 16);
   strncat(sql, addX(name2), 16);
   strcat(sql, "(ID INT, mesage varchar);");
   fprintf(stderr, "%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "INSERT ERROR: %s\n", zErrMsg);
   }

}

bool InsertUser(char name[16], char password[8]) {
   //check if user exist
   sqlite3_stmt* stmt;
   sqlite3_prepare_v2(db, "select user, password from users", -1, &stmt, 0);

   const unsigned char *_name;
   char __name[16];
   while (sqlite3_step(stmt) != SQLITE_DONE) {

      _name = sqlite3_column_text(stmt, 0);

      for (int i = 0; i < 16; i++) {
         __name[i] = _name[i];
      }

      if (!(strncmp(addX(name), __name, 16))) {
         return false;
      }
   }

   //add user to the table of users
   char* zErrMsg = 0;
   char sql[100] = "insert into users VALUES('";
   strncat(sql, addX(name), 16);
   strcat(sql, "', '");
   strncat(sql, password, 8);
   strcat(sql, "');");

   fprintf(stderr, "%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
   if (rc != SQLITE_OK) {
      fprintf(stderr, "INSERT ERROR: %s\n", zErrMsg);
      return false;
   }

   //table of chats for new user
   bzero(sql, 100);
   strcpy(sql, "CREATE TABLE IF NOT EXISTS ");
   strncat(sql, addX(name), 16);
   strcat(sql, "(chat varchar, newmesg int);");
   fprintf(stderr, "%s\n", sql);
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
      return false;
   }else {
      fprintf(stderr, "Created table successfully\n");
   }

   return true;
}

bool GetUser(char name[16], char password[8]) {
   sqlite3_stmt* stmt;
   sqlite3_prepare_v2(db, "select user, password from users", -1, &stmt, 0);

   const unsigned char *_name;
   const unsigned char *_password;

   char __name[16];
   char __password[8];

   while (sqlite3_step(stmt) != SQLITE_DONE) {

      _name = sqlite3_column_text(stmt, 0);
      _password = sqlite3_column_text(stmt, 1);

      
      fprintf(stdout, "NAME: %s  PASSWORD: %s\n", _name, _password);
      fprintf(stdout, "TO COMPARE NAME: %s  PASSWORD: %s\n", name, password);

      for (int i = 0; i < 16; i++) {
         __name[i] = _name[i];
      }

      for (int i = 0; i < 8; i++) {
         __password[i] = _password[i];
      }


      if (!(strncmp(addX(name), __name, 16))) {
         if (!(strncmp(addX(password), __password, 8))) {
            fprintf(stdout, "same\n");
            return true;
         }
      }

   }

   return false;
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

   sql = "CREATE TABLE IF NOT EXISTS users(user varchar, password varchar);";
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Created table successfully\n");
   }

   return 0;
}




