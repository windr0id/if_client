#ifndef SIGN_H
#define SIGN_H

#include "msocket.h"

#define MAX_DATA_NUM 24

bool get_status();
char* get_username();
int login(int id, char* password, int passwordlen);
int signup(char* username, int usernamelen,char* password, int passwordlen);

#endif // SIGN_H
