#ifndef P2P_H
#define P2P_H
#include <QObject>
#include <QThread>
#include <QtCore>
#include "msocket.h"

class p2p : public QThread
{
    Q_OBJECT
public:
    void run();
    p2p(int destid, QString fname, int fsize);
    void enable_req_back();
    int request();
    int recv();
signals:

private:
    int destid;
    QString fname;
    int fsize;
    int req_back;
};

#endif // P2P_H
