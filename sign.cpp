#include "sign.h"

bool logined = false;
char username[21];

bool get_status(){
    return logined;
}

char* get_username(){
    return username;
}

int login_back(char* out_username){
    //s->c	title:21	num:1	data0:<char>username[max:20]
    //登录成功
    //s->c	title:29	num:0
    //登录失败
    char buff[BUFF_LEN];
    m_recv(buff);
    int title;
    int num;
    char* (pdata)[MAX_DATA_NUM];
    int datalen[MAX_DATA_NUM];
    t_parse(buff, &title, &num, pdata, datalen);
    if(title == 21){
        memcpy(out_username, pdata[0], datalen[0]);
        return 0;
    }else if(title == 29){
        qDebug()<<"login_back title code 29";
        return -1;
    }else{
        qDebug()<<"login_back unknow title";
        return -2;
    }
}

int login(int id, char* password, int passwordlen){
    //c->s	title:20	num:2	data0:<int>userid	data1:<char>password[max:20,min:6]
    //发送登录请求
    char buff[BUFF_LEN];

    int title = 20;
    int num = 2;
    setHead(buff, title, num);

    int datalen[num] = {4, passwordlen};
    char c_id[4];
    IntToByteArray(id, c_id);
    char* (pdata)[num] = {c_id, password};
    int len = setData(buff, num, pdata, datalen);
    m_send(buff, len);

    if(login_back(username) != 0){
        return -1;
    }else{
        logined = true;
        return 0;
    }
}

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

    m_send(buff, len);

    return 0;
}
