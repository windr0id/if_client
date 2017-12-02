#include "msocket.h"

int server_fd;
int remote_fd;

using namespace std;

int m_init(){
    struct sockaddr_in servaddr;
    server_fd = socket(AF_INET , SOCK_STREAM, 0);
    //cout<<clint_fd<<endl;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP);
    servaddr.sin_port = htons(PORT);

    int erno;
    if((erno = connect(server_fd, (struct sockaddr*)&servaddr, sizeof(servaddr))) <0){
        cout<<" connect err:"<<erno<<endl;
    }
    return 0;
}

int m_send(const char* buff, int len){
    if(send(server_fd, buff, len, 0)<0){
        qDebug()<<"msocket=>m_send: send error.";
        return -1;
    }else{
        qDebug()<<"msocket=>m_send: send success.";
    }
    return 0;
}

int m_recv(char* buff){
    int n;
    if((n = recv(server_fd, buff, BUFF_LEN, 0)) < 0){
        qDebug()<<"msocket=>m_recv error.";
    }else{
        return n;
    }
}

void m_close(){
    close(server_fd);
}

int m_p2p_init(char* remote_ip, int remote_port){
    struct sockaddr_in remoteaddr;
    remote_fd = socket(AF_INET , SOCK_DGRAM, 0);
    //cout<<remote_fd<<endl;
    memset(&remoteaddr, 0, sizeof(remoteaddr));
    remoteaddr.sin_family = AF_INET;
    remoteaddr.sin_addr.s_addr = inet_addr(remote_ip);
    remoteaddr.sin_port = htons(remote_port);



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
