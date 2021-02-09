#include <iostream>
#include <sqlite3.h>

#include "auth/auth.h"

using namespace std;

// int callback(void *, int, char**, char**);

void login(){
    char username[50];
    char password[50];
    cout<<"Enter your username"<<endl;
    cin>>username;
    cout<<"Enter your password"<<endl;
    cin>>password;
    char msg[200];
    

}

void registeruser(){
    char username[50];
    char password[50];
    cout<<"Enter your username"<<endl;
    cin>>username;
    cout<<"Enter your password"<<endl;
    cin>>password;
    char msg[200];
    while(register_user(username, password, msg)){
        cout<<msg<<endl;
        
        cout<<"Enter your username"<<endl;
        cin>>username;
        cout<<"Enter your password"<<endl;
        cin>>password;
    }

    cout<<"Registered Successfully"<<endl;
}

int main(){
    // std::cout<<"Hello World";
    int r = initialise_auth();
    if(r){
        cout<<"Something went wrong! Try restarting.";
    }
    int selection;
    option: cout<<"Enter 1 for Sign In, 2 for Registering"<<endl;
    cin>>selection;
    if(selection==1){
        login();
    }else if(selection==2){
        registeruser();
    }else {
        cout<<"Please enter a vaild number"<<endl;
        goto option;
    }

   
    
    
    close_auth();
    return 0;
}



