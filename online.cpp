#include "online.h"

int getOnluser(int* n, int ids[], char unames[][21]){
    //c->s	title:40	num:0
    //发送查询请求
    //s->c	title:41	num:2x	data0:<int>userid0	data1:<char>username0[] ...
    //返回在线用户的id和用户名
    //s->c	title:49	num:0
    //查询失败
    char buff[BUFF_LEN];
    int title = 40;
    int num = 0;
    setHead(buff, title, num);
    m_send(buff, 8);

    m_recv(buff);
    char* (pdata)[100];
    int datalen[100];
    t_parse(buff, &title, &num, pdata, datalen);
    *n = num/2;
    for(int i=0; i<*n; i++){
        ids[i] = ByteArrayToInt(pdata[i*2]);
        memcpy(unames[i], pdata[i*2+1], strlen(pdata[i*2+1])+1);
    }
    return 0;

}
