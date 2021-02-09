#include "auth.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <openssl/sha.h>
#include "auth_model.h"

using namespace std;

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


int register_user(const char* username, const char* password, char* msg){
    int r = validate_password(password, msg);
    if(r>0){
        return r;
    }
    unsigned char hashed[33];
    string usern = username;
    string passw = password;
    string pre = usern + passw;
    SHA256((unsigned char*) pre.c_str(), pre.length(), hashed);
    
    hashed[32]='\0';

    
    unsigned long id = reinterpret_cast<uint64_t>(&pre);

    insert_user(username, (const char*) hashed, to_string(id).c_str());
    return 0;
}

int verify_credentials(const char* username, const char* hashedkey, char* uid){

}

int signin_user(const char* username, const char* password, char* msg, char* uid){
    unsigned char hashed[33];
    string usern = username;
    string passw = password;
    string pre = usern + passw;
    SHA256((unsigned char*) pre.c_str(), pre.length(), hashed);
    hashed[32]='\0';
    
}