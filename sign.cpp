#include "sign.h"


int signup(char* username, int usernamelen, char* password, int passwordlen){
    //c->s	title:10	num:2	data0:<char>username[max:20]	data1:<char>password[max:20,min:6]
    //发送注册请求
    char buff[BUFF_LEN];

    int title = 10;
    int num = 2;
    setHead(buff, title, num);

    int datalen[num] = {usernamelen, passwordlen};
    char* (pdata)[num] = {username, password};
    int len = setData(buff, num, pdata, datalen);

    for(int i=0; i<30; i++){
        qDebug()<<(int)buff[i];
    }

    m_send(buff, len);

    return 0;
}
