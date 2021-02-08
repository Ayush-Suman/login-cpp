#include "auth.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <openssl/sha.h>

#ifndef USER_TABLE
#define USER_TABLE "UserCred.db"
#endif

using namespace std;

sqlite3* db;

int validate_password(const char* password, char* msg){
    int len=strlen(password);
    if(len<8){
        sprintf(msg, "Password must be longer than 8");
        return 1;
    }
    int val=0;
    
    for(int i = 0; i<len; i++){
        if(password[i] <= 'Z' && password[i] >= 'A'){
            val|=1;
        }else if(password[i] <= 'z' && password[i] >= 'a'){
            val|=2;
        }else if(password[i] <= '9' && password[i] >= '0'){
            val|=4;
        }else{
            val|=8;
        }
        //cout<<i<<endl;
    }
    
    if(val<7){
        sprintf(msg, "Weak Password. Password must contain atleast an uppercase letter, a lowercase letter and a numeric value.");
        return 1;
    }
    if(val > 7){
        sprintf(msg, "Don't use special letters like @ # or $");
        return 1;
    }
    return 0;

}

// Exposed Functions

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

int register_user(const char* username, const char* password, char* msg){
    //cout<<"Register User"<<endl;
    int r = validate_password(password, msg);
    if(r>0){
        return r;
    }
    unsigned char hashed[33];
    string usern = username;
    string passw = password;
    string pre = usern + passw;
    SHA256((unsigned char*) pre.c_str(), pre.length(), hashed);
    //cout<<hashed<<endl;
    hashed[32]='\0';
    //cout<<"Hashed"<<endl;
    //string hashkey = b64decode(hashed);
    //cout<<hashkey<<endl;
    
    unsigned long id = reinterpret_cast<uint64_t>(&pre);
    char insert_user[500];
    sprintf(insert_user, "INSERT INTO USERCREDS (ID, USERNAME, KEY) VALUES (%ld, %s, %s)", id, username, hashed);
    sqlite3_exec(db, insert_user, NULL, 0, NULL);
    return 0;
}
