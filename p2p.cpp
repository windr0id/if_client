#include "p2p.h"

p2p::p2p(int destid, QString path, int fsize){
    this->destid = destid;
    this->fname = QFileInfo(path).fileName();
    this->fsize = fsize;
    req_back = 0;
}

void p2p::enable_req_back(){
    req_back = 1;
}

int p2p::request(){
    //c->s	title:50	num:4	data0:<int>tag	data1:<int>destid	data2:<int>filesize	data3:<char>filename[max:256]
    //发起传输请求
    char buff[BUFF_LEN];
    int title = 50;
    int num = 4;
    setHead(buff, title, num);

    int tag = 0;
    char c_tag[4];
    IntToByteArray(tag, c_tag);
    char c_destid[4];
    IntToByteArray(destid, c_destid);
    char c_fsize[4];
    IntToByteArray(fsize, c_fsize);
    char *c_fname = fname.toLatin1().data();
    int datalen[4] = {4, 4, 4, this->fname.size()};
    char* (pdata)[4] = {c_tag, c_destid, c_fsize, c_fname};
    int len = setData(buff, num, pdata, datalen);

    m_send(buff, len);

    // wait 5s
    for(int t = 0; t<50; t++){
        if(req_back != 0){
            return req_back;
        }
        msleep(100);
    }
    return 0;
}

void p2p::run()
{


    while(true){

        qDebug()<<"Send file From worker thread: "<<currentThreadId();
    }
}

