#ifndef THREAD_MES_H
#define THREAD_MES_H

#define BUFF_LEN 4096

#include <QThread>
#include <QDebug>
#include "message.h"

class thread_message : public QThread
{
    Q_OBJECT
public:
    void run();
signals:
    void mesin(int tag, int sourceid, QString message);
private:
    char buff[BUFF_LEN];
    int tag, sourceid;
    QString message;
};


#endif // THREAD_MES_H
