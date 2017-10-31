#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

#include <string>
#include "message.h"
#include "sign.h"
#include "online.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_init();
    t_m = new thread_message();
    ui->setupUi(this);
    DialogSignup *dsu = new DialogSignup;
    dsu->exec();

    refresh_online();
    selected_id = -1;

    connect(t_m, SIGNAL(mesin(int,int,QString)), this, SLOT(on_mesin(int,int,QString)));
    if(t_m->isRunning() == false){
        t_m->start();
    }

}

void MainWindow::on_mesin(int tag, int sourceid, QString message){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    this->ui->textBrowser->append(get_username_by_id(sourceid)+" - "+current_date+":");
    this->ui->textBrowser->append(message);
}

QString MainWindow::get_username_by_id(int id){
    //refresh_online();
    QListWidget* listWidget = this->ui->listWidget;
    for(int i=0; i<listWidget->count(); i++){
        if(listWidget->item(i)->data(Qt::UserRole).toInt() == id){
            return listWidget->item(i)->text();
        }
    }
    return "ID = "+QString::number(id);
}

void MainWindow::refresh_online(){
    int n;
    int ids[100];
    char unames[100][21];
    if(t_m->isRunning()){
        t_m->exit();
    }
    getOnluser(&n, ids, unames);
    if(t_m->isRunning() == false){
        qDebug()<<"t_m->start();";
        t_m->start();
    }
    QListWidget* listWidget = this->ui->listWidget;
    listWidget->clear();
    for(int i=0; i<n; i++){
        QListWidgetItem* l = new QListWidgetItem(listWidget);
        l->setData(Qt::UserRole, ids[i]);//set id to data
        l->setText(unames[i]);
        listWidget->addItem(l);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
    m_close();
}

void MainWindow::on_Button_send_clicked()
{
    if(selected_id == -1){
        this->ui->label_info->setText("No user selected.");
        return;
    }
    QString qs_text = this->ui->textEdit->document()->toPlainText();
    QByteArray qb_text = qs_text.toLatin1();
    char* c_text = qb_text.data();
    int meslen = qb_text.length();
    send_message(selected_id, c_text, meslen);
    this->ui->textEdit->clear();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    this->ui->label_info->setText(QString("Messaging with: ")+item->text());
    selected_id = item->data(Qt::UserRole).toInt();
}

void MainWindow::on_Button_refresh_clicked()
{
    refresh_online();
    selected_id = -1;
    this->ui->label_info->setText("Select a user to send message.");
}
