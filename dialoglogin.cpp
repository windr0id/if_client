#include <QCloseEvent>
#include "dialoglogin.h"
#include "ui_dialoglogin.h"

#include "sign.h"

DialogSignup::DialogSignup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSignup)
{
    ui->setupUi(this);
}

DialogSignup::~DialogSignup()
{
    delete ui;
}

void DialogSignup::on_buttonBox_rejected()
{
    exit(0);
}

void DialogSignup::on_buttonBox_accepted()
{
    int id = 10003;
    char* pass = "123456";
    QString s_id = this->ui->usernameEdit->toPlainText();
    id = s_id.toInt();
    qDebug()<<id;
    if(login(id, 4, pass, strlen(pass)+1) != 0){
        //do something
        qDebug()<<"info incorrect";
    }else{
        qDebug()<<get_username();
    }
}


void DialogSignup::closeEvent(QCloseEvent *event)
{
    if(get_status() == false){
        //exit(0);
    }
}
