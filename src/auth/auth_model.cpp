#include "auth_model.h"
#include <sqlite3.h>
#include <iostream>


#ifndef USER_TABLE
#define USER_TABLE "UserCred.db"
#endif

using namespace std;

sqlite3* db;

int initialise_auth(){
    int r = sqlite3_open(USER_TABLE, &db);
    if(r){
        return 1;
        }
    const char* create_table = "CREATE TABLE IF NOT EXISTS USERCREDS ("
        "ID INT PRIMARY KEY,"
        "USERNAME TEXT NOT NULL,"
        "KEY TEXT NOT NULL"
    ")";

    sqlite3_exec(db, create_table, NULL , 0, NULL);
}

void close_auth(){
    sqlite3_close(db);
}

void insert_user(const char* username, const char* hashedkey, const char* uid){
    char insert_user[500];
    sprintf(insert_user, "INSERT INTO USERCREDS (ID, USERNAME, KEY) VALUES (%ld, %s, %s)", uid, username, hashedkey);
    sqlite3_exec(db, insert_user, NULL, 0, NULL);
}