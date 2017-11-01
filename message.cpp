#include "message.h"

void MessageClass::run()
{
    while(true){
        this->get();
        qDebug()<<"get_message From worker thread: "<<currentThreadId();
    }
}

int MessageClass::get(){
    char buff[BUFF_LEN];
    int title;
    int num;
    char* (pdata)[1024];
    int datalen[1024];
    m_recv(buff);
    t_parse(buff, &title, &num, pdata, datalen);

    if(title == 33){
        //s->c	title:33	num:3	data0:<int>-tag	data1:<int>sourceid	data2:<char>message[max:4000]
        //分发标识为-tag的消息
        int tag = ByteArrayToInt(pdata[0]);
        int sourceid = ByteArrayToInt(pdata[1]);
        QString message = pdata[2];
        emit mesin(tag, sourceid, message);
        return 0;
    }else if(title == 41){
        //s->c	title:41	num:2x	data0:<int>userid0	data1:<char>username0[] ...
        //返回在线用户的id和用户名
        int n = num/2;
        for(int i=0; i<n; i++){
            int id = ByteArrayToInt(pdata[i*2]);
            QString name = pdata[i*2+1];
            emit onluserin(id, name);
        }
        return 0;
    }else{
        qDebug()<<"get_message error: "<<title;
        return -1;
    }
}


int MessageClass::send(int destid, char* message, int meslen){
    //c->s	title:30	num:3	data0:<int>tag	data1:<int>destid	data2:<char>message[max:4000]
    //向desid发送标识码为tag的消息
    char buff[BUFF_LEN];

    int title = 30;
    int num = 3;
    setHead(buff, title, num);

    int tag = 5555;
    char c_tag[4];
    IntToByteArray(tag, c_tag);

    char c_destid[4];
    IntToByteArray(destid, c_destid);

    int datalen[3] = {4, 4, meslen};
    char* (pdata)[3] = {c_tag, c_destid, message};
    int len = setData(buff, num, pdata, datalen);

    m_send(buff, len);
    return 0;
}
