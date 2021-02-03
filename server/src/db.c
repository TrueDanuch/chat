#include "server.h"

int DataBase() {
   sqlite3 *db;
   sqlite3_stmt* stmt;
   char *zErrMsg = 0;
   int rc;
   char *sql;


   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   sql = "CREATE TABLE IF NOT EXISTS users( id INT, user varchar, password varchar);";
   rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR: %s\n", zErrMsg);
   }else {
      fprintf(stderr, "Created table successfully\n");
   }

   for (int i = 0; i < 10; i++) {
      char strID[100];
      sprintf(strID, "%d", i);
      strID[1] = '\0';
      char sql1[100] = "insert into users VALUES (\0";

      strcat(sql1, strID);
      
      strcat(sql1, ", 'Andrii', 'pasword');");


      fprintf(stdout, "%s\n", strID);
      rc = sqlite3_exec(db, sql1, NULL, NULL, &zErrMsg);
      if (rc != SQLITE_OK) {
         fprintf(stderr, "IINSERT ERROR: %s\n", zErrMsg);
      }
   }

   sqlite3_prepare_v2(db, "select id, user, password from users", -1, &stmt, 0);
   int id1;
   const unsigned char *name;
   //char *passwd;
   for (int i = 0; i < 6; i++) {
      sqlite3_step(stmt);
      id1 = sqlite3_column_int(stmt, 0);

      name = sqlite3_column_text(stmt, 1);

      fprintf(stdout, "ID: %d NAME: %s\n", id1, name);
   }

   sqlite3_close(db);
   return 0;
}




