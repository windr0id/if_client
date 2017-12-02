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

#define IP "192.168.31.159"
#define PORT 9762
#define BUFF_LEN 4096
#define MAX_DATA_LEN 1024

int m_init();
int m_send(const char* buff, int len);
int m_recv(char* buff);
void m_close();

int m_test();

#endif // MSOCKET_H
