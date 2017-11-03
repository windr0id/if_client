#include <QCloseEvent>
#include "dialoglogin.h"
#include "ui_dialoglogin.h"

#include "sign.h"

bool b_signup = false;

DialogSignup::DialogSignup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSignup)
{
    ui->setupUi(this);
    this->ui->label_3->hide();
    this->ui->lineEditPASS2->hide();
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
    int id;
    char* pass;
    QString s_id = this->ui->lineEditID->text();
    QString s_pass = this->ui->lineEditPASS->text();
    QString s_pass2 = this->ui->lineEditPASS2->text();
    QByteArray qb = s_pass.toLatin1();
    pass = qb.data();


    if(b_signup){
        if(s_pass != s_pass2 || s_pass.length()<6){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, "info", "Password require more than 6 characters OR Repass is different to pass.");
            if (reply == QMessageBox::Ok)
                qDebug()<<"ok";
            else
                qDebug()<<"escape";
        }
    }else{
        if(qb.length() == 0){
            pass = "123456";
        }
        id = s_id.toInt();
        if(login(id, pass, strlen(pass)+1) != 0){
            //do something
            qDebug()<<"info incorrect";
        }else{
            qDebug()<<get_username();
        }
    }

}

void DialogSignup::closeEvent(QCloseEvent *event)
{
    if(get_status() == false){
        exit(0);
    }
}

void DialogSignup::on_signupButton_clicked()
{
    b_signup = true;
    this->ui->label_3->show();
    this->ui->lineEditPASS2->show();
    this->ui->label_4->hide();
    this->ui->signupButton->hide();
    this->ui->label->setText("Nickname:");

}
