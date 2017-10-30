#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

#include <string>
#include "thread_mes.h"
#include "message.h"
#include "sign.h"
#include "online.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_init();
    ui->setupUi(this);
    DialogSignup *dsu = new DialogSignup;
    dsu->exec();

    int n;
    int ids[100];
    char unames[100][21];
    getOnluser(&n, ids, unames);
    QListWidget* listWidget = this->ui->listWidget;
    for(int i=0; i<n; i++){
        QListWidgetItem* l = new QListWidgetItem(unames[i], listWidget);
        l->setData(0, ids[i]);//set id to data
        listWidget->addItem(l);
    }

    thread_message *t = new thread_message();
    connect(t, SIGNAL(mesin(int,int,QString)), this, SLOT(on_mesin(int,int,QString)));
    t->start();

}

void MainWindow::on_mesin(int tag, int sourceid, QString message){
    this->ui->textBrowser->append(message);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_close();
}

void MainWindow::on_Button_send_clicked()
{
    QString qs_text = this->ui->textEdit->document()->toPlainText();
    QByteArray qb_text = qs_text.toLatin1();
    char* c_text = qb_text.data();
    int meslen = qb_text.length();
    send_message(10003, c_text, meslen);
    //this->ui->textEdit->clear();
}

void MainWindow::on_Button_login_clicked()
{
    m_close();
    m_init();
    char* u = "user3";
    char* p = "123123";
    signup(u, strlen(u)+1, p, strlen(p)+1);
}
