#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin.h"
#include <QDebug>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_init();
    ui->setupUi(this);
    DialogSignup *dsu = new DialogSignup;
    dsu->exec();


    m_c = new MessageClass();

    refresh_online();
    selected_id = -1;

    connect(m_c, SIGNAL(mesin(int,int,QString)), this, SLOT(on_mesin(int,int,QString)));
    connect(m_c, SIGNAL(onluserin(int,QString)), this, SLOT(on_onluserin(int,QString)));

    if(m_c->isRunning() == false){
        m_c->start();
    }

}

void MainWindow::on_mesin(int tag, int sourceid, QString message){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh:mm:ss ");
    this->ui->textBrowser->append("-----------");
    this->ui->textBrowser->append(current_date+get_username_by_id(sourceid)+" :");
    this->ui->textBrowser->append(message);
}

void MainWindow::on_onluserin(int id, QString name){
    QListWidget* listWidget = this->ui->listWidget;
    QListWidgetItem* l = new QListWidgetItem(listWidget);
    l->setData(Qt::UserRole, id);//set id to data
    l->setText(name);
    listWidget->addItem(l);
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
    QListWidget* listWidget = this->ui->listWidget;
    listWidget->clear();
    getOnluser();
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
    m_c->send(selected_id, c_text, meslen);
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
