#include "message.h"


int get_message(char* buff, int &tag, int &sourceid, QString &message){
    //s->c	title:33	num:3	data0:<int>-tag	data1:<int>sourceid	data2:<char>message[max:4000]
    //分发标识为-tag的消息
    int title;
    int num;
    char* (pdata)[num];
    int datalen[num];
    m_recv(buff);
    t_parse(buff, &title, &num, pdata, datalen);

    if(title == 33){
        tag = ByteArrayToInt(pdata[0]);
        sourceid = ByteArrayToInt(pdata[1]);
        message = pdata[2];
        return 0;
    }else{
        qDebug()<<"get_message error: "<<title;
        return -1;
    }
}


int send_message(int destid, char* message, int meslen){
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
