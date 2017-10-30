#include "thread_mes.h"

void thread_message::run()
{
    while(true){
        get_message(buff, tag, sourceid, message);
        qDebug()<<"get_message:"<<tag<<" "<<sourceid<<" "<<message<<" From worker thread: "<<currentThreadId();
        for(int i=0; i<35; i++){
            qDebug()<<buff[i];
        }
        emit mesin(tag, sourceid, message);
    }
}

