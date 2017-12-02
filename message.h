#ifndef WRAPPER_H
#define WRAPPER_H

#include <QObject>
#include <QThread>
#include <QtCore>
#include "msocket.h"

class MessageClass : public QThread
{
    Q_OBJECT
public:
    void run();
    int get();
    int send(int destid, char* message, int meslen);

signals:
    void mesin(int tag, int sourceid, QString message);
    void onluserin(int id, QString name);
    void p2p_req_in(int tag, int sourceid, int filesize, QString filename);
};

#endif // WRAPPER_H
