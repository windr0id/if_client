#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtCore>
#include "msocket.h"

int get_message(char* buff, int &tag, int &sourceid, QString &message);
int send_message(int destid, char* message, int meslen);

#endif // WRAPPER_H
