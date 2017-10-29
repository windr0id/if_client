#include "message.h"

//c->s	title:30	num:3	data0:<int>tag	data1:<int>destid	data2:<char>message[max:4000]
//向desid发送标识码为tag的消息
int send_message(int destid, char* message, int meslen){
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
