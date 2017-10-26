#ifndef MSOCKET_H
#define MSOCKET_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <QDebug>
#include "tools.h"

#define IP "127.0.0.1"
#define PORT 9762
#define BUFF_LEN 4096
#define DATA_LEN 4000

int m_init();
int m_send(const char* buff, int len);
int m_test();
void m_close();


#endif // MSOCKET_H
