#include "msocket.h"

int clint_fd;

using namespace std;

int m_init(){

    struct sockaddr_in clinaddr;

    clint_fd = socket(AF_INET , SOCK_STREAM, 0);
    //cout<<clint_fd<<endl;
    memset(&clinaddr, 0, sizeof(clinaddr));
    clinaddr.sin_family = AF_INET;
    clinaddr.sin_addr.s_addr = inet_addr(IP);
    clinaddr.sin_port = htons(PORT);

    int erno;
    if((erno = connect(clint_fd, (struct sockaddr*)&clinaddr, sizeof(clinaddr))) <0){
        cout<<" connect err:"<<erno<<endl;
    }
    return 0;
}

int m_send(const char* buff, int len){
    if(send(clint_fd, buff, len, 0)<0){
        qDebug()<<"msocket=>m_send: send error.";
        return -1;
    }else{
        qDebug()<<"msocket=>m_send: send success.";
    }
    return 0;
}

void m_close(){
    close(clint_fd);
}

int m_test(){
    char buff[BUFF_LEN];
    char title[4];
    IntToByteArray(10, title);
    char num[4];
    IntToByteArray(2, num);

    char len0[4];
    IntToByteArray(4, len0);
    char data0[4];
    IntToByteArray(976284, data0);

    char len1[4];
    IntToByteArray(4, len1);
    char data1[4];
    IntToByteArray(396, data1);

    memcpy((void*)(buff), (void*)title, 4);
    memcpy((void*)(buff+4), (void*)num, 4);
    memcpy((void*)(buff+8), (void*)len0, 4);
    memcpy((void*)(buff+12), (void*)data0, 4);
    memcpy((void*)(buff+16), (void*)len1, 4);
    memcpy((void*)(buff+20), (void*)data1, 4);

    m_send(buff, 24);
    return 0;
}
